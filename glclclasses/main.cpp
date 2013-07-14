#include "engInit.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>

void error_callback	(int error, const char* description)
{
    fputs(description, stderr);
}

int main(int argc, char **argv)
{
    std::vector<const char*> log;
    EngInit initclgl;
    initclgl.SetHint({GLFW_SAMPLES,4,GLFW_CONTEXT_VERSION_MAJOR,4,GLFW_CONTEXT_VERSION_MINOR,2,GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE});
    EngErrFunct f1;
    f1.func = error_callback;
    initclgl.SetCallback (f1);
    initclgl.Init("test",800,640);
    std::cout<<"Platforms: "<<initclgl.GetNumPlatforms()<<std::endl;
    initclgl.CreateContext(0);
    EngPlatform* MainPlatform = initclgl.GetEngPlatform(0);
    log = initclgl.GetErrLog();
    std::cout<<"Errors:\n";
    for (auto p = log.begin(); p!=log.end(); ++p)
        std::cerr<<'\t'<<*p<<std::endl;
    initclgl.ClearErrLog();
    std::cout<<"Debug Info:\n";
    log = initclgl.GetLog();
    for (auto p = log.begin(); p!=log.end(); ++p)
        std::cout<<'\t'<<*p<<std::endl;
    initclgl.ClearLog();
    cl_command_queue command_queue = NULL;
    cl_mem memobj = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    char outstr[14];
    std::string str;
    std::ifstream in;
    in.open("hello.cl");
    std::getline(in,str,'\0');
    in.close();
    cl_int ret;
    command_queue = clCreateCommandQueue(MainPlatform->context, MainPlatform->devices[0], 0, &ret);
    if (ret!=CL_SUCCESS)
            std::cerr<<"Something gonna wrong1\n";
    memobj = clCreateBuffer(MainPlatform->context, CL_MEM_READ_WRITE,14 * sizeof(char), NULL, &ret);
    if (ret!=CL_SUCCESS)
            std::cerr<<"Something gonna wrong2\n";
    char* buff = (char*) str.c_str();
    size_t size = str.size();
    program = clCreateProgramWithSource(MainPlatform->context, 1, (const char**)&buff,&size, &ret);
    if (ret!=CL_SUCCESS)
        std::cerr<<"Something gonna wrong3\n";
    ret = clBuildProgram(program, 1, & MainPlatform->devices[0], NULL, NULL, NULL);
    kernel = clCreateKernel(program, "hello", &ret);
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
    ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);
    ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,14 * sizeof(char),outstr, 0, NULL, NULL);
    std::cout<<outstr<<std::endl;
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(memobj);
    ret = clReleaseCommandQueue(command_queue);
    glClearColor(0.0f,0.0f,1.0f, 0.0f);
    while (glfwGetKey(MainPlatform->window,GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(MainPlatform->window);
    }
    initclgl.Destroy();
    return 0;
}
