#include <iostream>
#include <fstream>
#include <cstdlib>
#include "engInit.hpp"


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
    initclgl.setHint({GLFW_VISIBLE,GL_FALSE});
    unsigned int win1 = initclgl.createGLWindow("Example 1",800,640);
    initclgl.setHint({GLFW_VISIBLE,GL_TRUE});
    unsigned int win2 = initclgl.createSharedGLWindow("Example 1 shared",win1,1027,768);
    initclgl.setCallback(KEYFUN,(void*)key_callback,NULL,win2);
    auto platform = initclgl.getEngGLPlatform(win2);
    std::vector<std::string> log = initclgl.getErrLog();
    std::cout<<"Errors: "<<std::endl;
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    log = initclgl.getLog();
    std::cout<<"Debug information:\n";
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    initclgl.setCurrentMonitor(win2);
    glClearColor(0.4,0.4,1.0,0.0);
    while (!glfwWindowShouldClose(platform->controll_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
    }
    initclgl.clearALL();
    return 0;
}
