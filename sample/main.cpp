 // Include standard headers
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "engInit.hpp"
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

void render_callback (const EngPlatform *platform, void *indata, void *outdata)
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
    initclgl.setHint({GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE, GLFW_CONTEXT_VERSION_MAJOR,4,GLFW_CONTEXT_VERSION_MINOR,3,GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE});
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
    render.setPlatform(platform);
    render.setRenderFunction(render_callback);
    render.render();
    while (!glfwWindowShouldClose(platform->window))
            glfwWaitEvents();
    render.stopRender();
    initclgl.destroy();
    return 0;
}
