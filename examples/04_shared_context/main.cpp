#include <iostream>
#include <engInit.hpp>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <vector>


using namespace std;

bool exit_thread;
bool data_write;
condition_variable cv;
mutex cv_m;
GLuint vbo;

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void MyThread( EngGLPlatform* win )
{
    glfwMakeContextCurrent( win->controll_window );

    glGenBuffers( 1, &vbo );
    srand(time(NULL));
    float temp[ 512 ];
    while( !exit_thread )
    {
        for( size_t i = 0; i < 512; i+=2 )
        {
            temp[ i+0 ] = rand() % 1366;
            temp[ i+1 ] = rand() % 768;
        }
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * 512, temp, GL_DYNAMIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glFlush();
        data_write = 1;
        cv.notify_one();
    }
}

int main()
{
    EngInit initgl;
    initgl.setCallback(ERRFUN,(void*)error_callback);
    initgl.setHint({GLFW_VISIBLE,GL_FALSE});
    unsigned int win1 = initgl.createGLWindow("Thread window",1,1);
    initgl.setHint({GLFW_VISIBLE,GL_TRUE});
    unsigned int win2 = initgl.createSharedGLWindow("Example 4",win1,800,600);
    initgl.setCurrentMonitor(win2);
    initgl.setCallback(KEYFUN,(void*)key_callback,NULL,win2);
    EngGLPlatform* thread_platform = initgl.getEngGLPlatform(win1);
    EngGLPlatform* platform = initgl.getEngGLPlatform(win2);
    thread vbo_thread (MyThread,thread_platform);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, 1366, 0, 768, -1, 1 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(2.0);
    while (!glfwWindowShouldClose(platform->controll_window))
    {
        std::unique_lock<std::mutex> lk(cv_m);
        cv.wait(lk, [](){return data_write == 1;});
        glClear( GL_COLOR_BUFFER_BIT );
        glEnableClientState( GL_VERTEX_ARRAY );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glVertexPointer( 2, GL_FLOAT, 0, 0 );
        glColor3ub( rand() % 256, rand() % 256, rand() % 256 );
        glDrawArrays( GL_POINTS, 0, 512 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glDisableClientState( GL_VERTEX_ARRAY );
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
        data_write = 0;
        lk.unlock();
    }
    exit_thread = 1;
    vbo_thread.join();
    initgl.clearALL();
    return 0;
}

