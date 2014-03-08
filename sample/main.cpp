 // Include standard headers
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "engRender.hpp"


void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void render_callback (const EngPlatform *platform,const Buffer *indata, Buffer *outdata, Buffer *from_pre, Buffer *to_post)
{
    GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glClearBufferfv(GL_COLOR, 0, red);
}

int main( void )
{
    EngInit initclgl;
    EngRender render;
    EngPlatform* platform;
    initclgl.setCallback(ERRFUN,(void*)error_callback);
    initclgl.init("Simple app",800,640);
    initclgl.setCallback(KEYFUN,(void*)key_callback);
    platform = initclgl.getEngPlatform(0);
    std::vector<std::string> log = initclgl.getErrLog();
    std::cout<<"Errors: "<<std::endl;
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    log = initclgl.getLog();
    std::cout<<"Debug information:\n";
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    auto controller = initclgl.getLocker();
    render.setPlatform(platform);
    render.setController(controller);
    render.setRenderFunction(ENGFUNCLOOP,(void*)render_callback);
    render.render();
    while (!glfwWindowShouldClose(platform->controll_window))
            glfwWaitEvents();
    render.stopRender();
    initclgl.destroy();
    return 0;
}
