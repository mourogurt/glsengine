#include <iostream>
#include <engInit.hpp>
#include <engCustomShader.hpp>
#include <engData.hpp>
#include <fstream>

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
    const float indata[4] = {1.0,0.0,0.5,1.0};
    EngAttribute data;
    data.setProgram(program);
    data.setName("vcolor\0");
    data.setLength(4);
    data.bind();
    glUseProgram(program);
    data.write(indata);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glPointSize(5.0);
    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, 1);
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
    } while (glfwGetKey(platform->controll_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
             glfwWindowShouldClose(platform->controll_window) == 0);
    data.clear();
    shader.cleanShader();
    initgl.clearALL();
    return 0;
}

