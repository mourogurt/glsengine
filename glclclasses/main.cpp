// Include standard headers
#include <iostream>
#include <fstream>

#include "engInit.hpp"
#include "engModel.hpp"
#include "engCompute.hpp"

EngModel gen_model (void* in,void* out)
{
    GLuint* VertexArrayID = new GLuint;
    glGenVertexArrays(1, VertexArrayID);
    glBindVertexArray(*VertexArrayID);
    GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };
    GLuint* vertexbuffer = new GLuint;
    glGenBuffers(1, vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, *vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    EngModel rmodel;
    rmodel.size_data = sizeof(g_vertex_buffer_data);
    rmodel.vertex_data = new GLfloat [rmodel.size_data];
    for (GLuint i = 0; i < rmodel.size_data; i++)
    {
        rmodel.vertex_data[i] = g_vertex_buffer_data[i];
    }
    rmodel.vertexBuffer = vertexbuffer;
    rmodel.vertexID = VertexArrayID;
    return rmodel;
}

EngCompute load_shader (void* inv, void* outv)
{
    EngCompute rshad;
    std::ifstream in;
    std::string source;
    in.open ("vertex.glsl");
    std::getline(in,source,'\0');
    in.close();
    rshad.vertex_source = new char[source.size()+1];
    for (size_t i = 0; i < source.size(); i++)
        rshad.vertex_source[i] = source[i];
    rshad.vertex_source += '\0';
    in.open ("fragment.glsl");
    std::getline(in,source,'\0');
    in.close();
    rshad.fragment_source = new char[source.size()+1];
    for (size_t i = 0; i < source.size(); i++)
        rshad.fragment_source[i] = source[i];
    rshad.fragment_source += '\0';
    return rshad;
}

int main( void )
{
    //Initialization class
    EngInit initclgl;
    //Array of EngModels class
    EngModelArray marray;
    //Functor to load in Array
    EngGenModelFunct genfunct;
    //Pointer to EngModel (vertex coordinate)
    EngModel* model1;
    //Pointer to platform (includes GLFWwindow*, cl_platform_id*, cl_device_id*, numDevices, cl_context)
    EngPlatform* platform;
    //Functor to load shaders in Shaders array
    EngLoadCompFunct comfunct;
    //Array of shaders class
    EngComputeArray shaders;
    //ID of gpu program
    GLuint programID;
    //Initialize window
    initclgl.init("chapter 2 completed");
    //Get the first detected platform
    platform = initclgl.getEngPlatform(0);
    //Load functions in functors
    genfunct.func = gen_model;
    comfunct.func = load_shader;
    //Add model to array
    marray.genModel(genfunct,nullptr);
    //Add shader to array
    shaders.addCompute(comfunct,nullptr);
    //Get the first added model
    model1 = marray.getModel(0);
    // create the gpu program
    int error;
    programID = shaders.createProgram(0,error);
    // Print errors
    std::vector<const char*> log = initclgl.getErrLog();
    std::cout<<"Errors: "<<std::endl;
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    initclgl.clearErrLog();
    log = shaders.getErrLog();
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    shaders.clearErrLog();
    log = initclgl.getLog();
    //print debug information
    std::cout<<"Debug information:\n";
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    initclgl.clearLog();
    log = shaders.getLog();
    for (size_t i = 0; i < log.size(); i++ )
        std::cout<<log[i]<<std::endl;
    shaders.clearLog();
    ////////////////////////////////////////////////////////////////////////////////
    //Print the number of platforms
    std::cout<<"Platforms: "<<initclgl.getNumPlatforms()<<std::endl;
    //Create context
    initclgl.createContext(0);
    //OpenCL program, later will be in engine
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
    command_queue = clCreateCommandQueue(platform->context, platform->devices[0], 0, &ret);
    if (ret!=CL_SUCCESS)
            std::cerr<<"error to create command queue\n";
    memobj = clCreateBuffer(platform->context, CL_MEM_READ_WRITE,14 * sizeof(char), NULL, &ret);
    if (ret!=CL_SUCCESS)
            std::cerr<<"error to create buffer\n";
    char* buff = (char*) str.c_str();
    size_t size = str.size();
    program = clCreateProgramWithSource(platform->context, 1, (const char**)&buff,&size, &ret);
    if (ret!=CL_SUCCESS)
         std::cerr<<"error to create program\n";
    ret = clBuildProgram(program, 1, & platform->devices[0], NULL, NULL, NULL);
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
    /////////////////////////////////////////////////////////////////////////////
    //Later will be in a engine render
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    do{
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
        // Use program
        glUseProgram(programID);
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, *(model1 -> vertexBuffer));
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(platform ->window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(platform -> window, GLFW_KEY_ESCAPE) != GLFW_PRESS && (!glfwWindowShouldClose(platform -> window)));
    //Release all memory, contexts, devices, e.t.c
    marray.destroy();
    shaders.destroy();
    initclgl.destroy();
    return 0;
}
