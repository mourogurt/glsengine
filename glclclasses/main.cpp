#include "engInit.hpp"
#include "engModel.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>

void error_callback	(int error, const char* description)
{
    std::cerr<<description<<" "<<error<<std::endl;
}

EngModel load_model (void* out, const char* path)
{
    out = nullptr;
    std::ifstream in(path);
    std::vector<GLfloat> tmpvctr;
    while (!in.eof())
    {
        int tmpint;
        in >> tmpint;
        tmpvctr.push_back(tmpint);
    }
    in.close();
    EngModel lmodel;
    lmodel.size_data = tmpvctr.size();
    lmodel.vertex_data = new GLfloat[lmodel.size_data];
    for (GLuint i = 0; i < tmpvctr.size(); i++)
        lmodel.vertex_data[i] = tmpvctr.at(i);
    glGenVertexArrays(1, &lmodel.vertexID);
    glBindVertexArray(lmodel.vertexID);
    glGenBuffers(1, &(lmodel.vertexBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, lmodel.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, lmodel.size_data,lmodel.vertex_data, GL_STATIC_DRAW);
    return lmodel;
}

int main()
{
    std::vector<const char*> log;
    EngInit initclgl;
    EngModelArray models;
    initclgl.SetHint({GLFW_SAMPLES,4,GLFW_CONTEXT_VERSION_MAJOR,4,GLFW_CONTEXT_VERSION_MINOR,2,GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE});
    EngErrFunct f1;
    EngLoadModelFunct f2;
    f1.func = error_callback;
    f2.func = load_model;
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
    models.loadModel(f2,"testModel");
    EngModel* md1;
    md1 = models.getModel(0);
    for (GLuint i = 0; i< md1 -> size_data; i++)
    {
        std::cout<<md1->vertex_data[i]<<"\t";
    }
    std::cout<<std::endl;
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
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, md1->vertexBuffer);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        glfwPollEvents();
        glfwSwapBuffers(MainPlatform->window);
    }
    models.Destroy();
    initclgl.Destroy();
    return 0;
}
