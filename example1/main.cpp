#include <iostream>
#include <fstream>
#include "engInit.hpp"
#include "engCustomShader.hpp"
#include "engData.hpp"


void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main( void )
{
    EngInit initclgl;
    initclgl.setCallback(ERRFUN,(void*)error_callback);
    initclgl.setHint({GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE,GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE,GLFW_CONTEXT_VERSION_MAJOR, 3,GLFW_CONTEXT_VERSION_MINOR, 3});
    unsigned int win1 = initclgl.createGLWindow("Custom shader test",800,640);
    initclgl.setCallback(KEYFUN,(void*)key_callback,NULL,win1);
    auto platform = initclgl.getEngGLPlatform(win1);
    std::vector<std::string> log = initclgl.getErrLog();
    std::cout<<"Errors: "<<std::endl;
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    log = initclgl.getLog();
    std::cout<<"Debug information:\n";
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    EngCustomShader shader;
    std:: ifstream in("vshader.glsl");
    std::string sources;
    getline(in,sources,'\0');
    in.close();
    shader.compileShaderStage(GL_VERTEX_SHADER,sources);
    in.open("fshader.glsl");
    sources.clear();
    getline(in,sources,'\0');
    in.close();
    shader.compileShaderStage(GL_FRAGMENT_SHADER,sources);
    shader.linkShader();
    GLuint program = shader.getProgramID();
    log = shader.getErrLog();
    std::cout<<"Errors: "<<std::endl;
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    log = shader.getLog();
    std::cout<<"Debug information:\n";
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    GLfloat data[4] = {1.0,0.0,0.5,1.0};
    glPointSize(10.0);
    EngAttribute objdata;
    objdata.setProgram(program);
    objdata.setName("vcolor\0");
    objdata.setLength(4);
    objdata.bind();
    glClearColor(0.4,0.4,1.0,0.0);
    glUseProgram(program);
    objdata.write(data);
    while (!glfwWindowShouldClose(platform->controll_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, 1);
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
    }
    shader.cleanShader();
    initclgl.clearALL();
    return 0;
}
