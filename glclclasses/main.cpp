// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "engInit.hpp"
#include "engModel.hpp"

EngModel gen_model (void* in,void* out)
{
    in = nullptr;
    out = nullptr;
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
    for (int i = 0; i < rmodel.size_data; i++)
    {
        rmodel.vertex_data[i] = g_vertex_buffer_data[i];
    }
    rmodel.vertexBuffer = vertexbuffer;
    rmodel.vertexID = VertexArrayID;
    return rmodel;

}

int main( void )
{

    EngInit initclgl;
    EngModelArray marray;
    EngGenModelFunct genfunct;
    EngModel* model1;
    initclgl.init("tutorial 2",800,640);
    genfunct.func = gen_model;
    marray.genModel(genfunct,nullptr);
    model1 = marray.getModel(0);
    EngPlatform* platform;
    platform = initclgl.getEngPlatform(0);
    // Ensure we can capture the escape key being pressed below
    //glfwEnable( GLFW_STICKY_KEYS );
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    do{
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
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
    marray.destroy();
    initclgl.destroy();
    return 0;
}
