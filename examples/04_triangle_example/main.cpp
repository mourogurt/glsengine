#include <iostream>
#include <fstream>
#include <engInit.hpp>
#include <engValue.hpp>
#include <engBuffer.hpp>
#include <engCustomShader.hpp>

using namespace std;

int main()
{
    EngInit initgl;
    unsigned win1 = initgl.createGLWindow("Example 4",800,600);
    EngGLPlatform* platform = initgl.getEngGLPlatform(win1);
    glfwSetInputMode(platform->controll_window, GLFW_STICKY_KEYS, GL_TRUE);
    EngCustomShader shader;
    EngGLAttribute attrib1;
    string src;
    ifstream in("vert.glsl");
    getline(in,src,'\0');
    in.close();
    shader.compileShaderStage(GL_VERTEX_SHADER,src);
    in.open("frag.glsl");
    getline(in,src,'\0');
    in.close();
    shader.compileShaderStage(GL_FRAGMENT_SHADER,src);
    shader.linkShader();
    GLuint program = shader.getProgramID();
    auto log = shader.getErrLog();
    for (unsigned i = 0; i < log.size(); i++)
        cout << log[i]<<endl;
    if (log.size() > 0) return 1;
    GLuint VAO;
    GLfloat pos[] = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
    };
    GLfloat color[4] = {0.5f,0.0f,0.0f,1.0f};
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    attrib1.setProgram(program);
    attrib1.bind("vcolor");
    attrib1.write(color,4);
    EngVBO buf1;
    buf1.allocate(sizeof(pos),GL_STATIC_DRAW,pos);
    buf1.setLocation("pos",program);
    glClearColor(0.3f,0.3f,0.3f,1.0f);
    glUseProgram(program);
    buf1.bind(3);
    buf1.enable();
    do
    {
        glClear(GL_COLOR_BUFFER_BIT);
        buf1.render(3);
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
    } while (glfwGetKey(platform->controll_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
             glfwWindowShouldClose(platform->controll_window) == 0);
    buf1.disable();
    buf1.clear();
    glDeleteVertexArrays(1,&VAO);
    return 0;
}

