#include <iostream>
#include <fstream>
#include "engRender.hpp"
#include <cstring>
#include <cstdio>

using namespace std;

GLuint LoadShaders(const char* vertex_file_path,const char* fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void pre_render_func (const EngPlatform*,const Buffer*, Buffer*, Buffer*, Buffer*);
void loop_func (const EngPlatform*,const Buffer*, Buffer*, Buffer*, Buffer*);
void post_loop_func(const EngPlatform*,const Buffer*, Buffer*, Buffer*, Buffer*);

void key_callback(GLFWwindow*, int, int, int, int);

int main()
{
    EngInit initclgl;
    EngRender render;
    initclgl.setHint({GLFW_CONTEXT_VERSION_MAJOR,3,GLFW_CONTEXT_VERSION_MINOR,3});
    initclgl.init("Example 2",800,640);
    initclgl.setCallback(KEYFUN,(void*)key_callback);
    initclgl.createContext(0);
    auto platform = initclgl.getEngPlatform(0);
    glClearColor(0.0,0.4,0.4,0.0);
    auto locker = initclgl.getLocker();
    render.setController(locker);
    render.setPlatform(platform);
    render.setRenderFunction(ENGFUNCPRELOOP,(void*)pre_render_func);
    render.setRenderFunction(ENGFUNCLOOP,(void*)loop_func);
    render.setRenderFunction(ENGFUNCPOSTLOOP,(void*)post_loop_func);
    render.render();
    while (!glfwWindowShouldClose(platform->window))
        glfwWaitEvents();
    render.stopRender();
    initclgl.destroy();
    return 0;
}

void pre_render_func(const EngPlatform *platform,const Buffer *indata, Buffer *outdata, Buffer *to_loop, Buffer *to_post)
{
    GLuint VAOID;
    GLuint vertexbuffer;
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };
    GLuint programID;
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glGenVertexArrays(1,&VAOID);
    glBindVertexArray(VAOID);
    programID = LoadShaders( "vertex.glsl", "fragment.glsl" );
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    to_loop->buff = new char[sizeof(GLuint) * 2];
    to_post->buff = new char[sizeof(GLuint) * 3];
    to_loop->buffsize = sizeof(GLuint) * 2;
    to_post->buffsize = sizeof(GLuint) * 3;
    memcpy(to_loop->buff,&vertexbuffer,sizeof(GLuint));
    memcpy(to_loop->buff + sizeof(GLuint),&programID,sizeof(GLuint));
    memcpy(to_post->buff,&VAOID,sizeof(GLuint));
    memcpy(to_post->buff + sizeof(GLuint),&vertexbuffer,sizeof(GLuint));
    memcpy(to_post->buff + (2*sizeof(GLuint)),&programID,sizeof(GLuint));
}

void loop_func (const EngPlatform *platform,const Buffer *indata, Buffer *outdata, Buffer *from_pre, Buffer *to_post)
{
    GLuint VBOID;
    GLuint programID;
    memcpy(&VBOID,from_pre->buff,sizeof(GLuint));
    memcpy(&programID,from_pre->buff + sizeof(GLuint),sizeof(GLuint));
    // 1rst attribute buffer : vertices
    glClear( GL_COLOR_BUFFER_BIT );
    glUseProgram(programID);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

void post_loop_func(const EngPlatform *platform,const Buffer *indata, Buffer *outdata, Buffer *from_pre, Buffer *from_loop)
{
    GLuint VAOID,VBOID,programID;
    memcpy(&VAOID,from_pre->buff,sizeof(GLuint));
    memcpy(&VBOID,from_pre->buff + sizeof(GLuint),sizeof(GLuint));
    memcpy(&programID,from_pre->buff + (2*sizeof(GLuint)),sizeof(GLuint));
    glDeleteProgram(programID);
    glDeleteBuffers(1, &VBOID);
    glDeleteVertexArrays(1, &VAOID);

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
