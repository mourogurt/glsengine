#include <iostream>
#include <fstream>
#include <cmath>
#include <engInit.hpp>
#include <engCustomShader.hpp>
#include <engValue.hpp>

using namespace std;

int main()
{
    EngInit initgl;
    unsigned win = initgl.createGLWindow("Example 3",800,600);
    EngGLPlatform* platform = initgl.getEngGLPlatform(win);
    glfwSetInputMode(platform->controll_window, GLFW_STICKY_KEYS, GL_TRUE);
    EngCustomShader shader;
    std:: ifstream in("vert.glsl");
    std::string sources;
    getline(in,sources,'\0');
    in.close();
    shader.compileShaderStage(GL_VERTEX_SHADER,sources);
    in.open("frag.glsl");
    sources.clear();
    getline(in,sources,'\0');
    in.close();
    shader.compileShaderStage(GL_FRAGMENT_SHADER,sources);
    shader.linkShader();
    GLuint program = shader.getProgramID();
    auto log = shader.getErrLog();
    for (unsigned i = 0; i < log.size(); i++)
        cout << log[i]<<endl;
    if (log.size() > 0) return 1;
    float color[4];
    float pos[4];
    EngGLAttribute value1,value2;
    GLuint VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    value1.setProgram(program);
    value1.bind("vcolor");
    value2.setProgram(program);
    value2.bind("position");
    glUseProgram(program);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glPointSize(5.0);
    float eps = 0.0;
    do {
        eps+=0.01;
        if (eps >= 100)
            eps = 0;
        pos[0] = cos(eps)*0.95;
        pos[1] = sin(eps)*0.95;
        pos[2] = 0.0f;
        pos[3] = 1.0f;
        color[0] = cos(eps);
        color[1] = sin(eps);
        color[2] = cos(eps)*cos(eps) + sin(eps)*sin(eps);
        color[3] = 1.0f;
        value2.write(pos,4);
        value1.write(color,4);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, 1);
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
    } while (glfwGetKey(platform->controll_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
             glfwWindowShouldClose(platform->controll_window) == 0);
    glDeleteVertexArrays(1,&VAO);
    shader.cleanShader();
    initgl.clearALL();
    return 0;
}

