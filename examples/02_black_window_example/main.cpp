#include <iostream>
#include <engInit.hpp>

using namespace std;

int main()
{
    EngInit initgl;
    unsigned num = initgl.createGLWindow("Black window example",800,600);
    EngGLPlatform* platform = initgl.getEngGLPlatform(num);
    glfwSetInputMode(platform->controll_window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    do {
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
    } while (glfwGetKey(platform->controll_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
             glfwWindowShouldClose(platform->controll_window) == 0);
    initgl.clearALL();
    return 0;
}

