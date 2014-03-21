#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <iostream>
#include <condition_variable>
#include <mutex>

using namespace std;

bool exit_thread;
bool data_write;
condition_variable cv;
mutex cv_m;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint vbo;
GLuint vao;

// reload shared VBO with random data every second
void MyThread( GLFWwindow* win )
{
    glfwMakeContextCurrent( win );
    //glewInit();

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

    if( !glfwInit() )
        return -1;
    glfwWindowHint( GLFW_VISIBLE, GL_FALSE );
    GLFWwindow* threadWin = glfwCreateWindow( 1, 1, "Thread Window", NULL, NULL );
    glfwWindowHint( GLFW_VISIBLE, GL_TRUE );
    GLFWwindow* window = glfwCreateWindow( 1366, 768, "Hello World", NULL, threadWin );
    glfwMakeContextCurrent( window );
    glewInit();
    glfwSetKeyCallback(window,key_callback);
    thread aThread( MyThread, threadWin );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, 1366, 0, 768, -1, 1 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(2.0);
    while( !glfwWindowShouldClose( window ) )
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
        glfwSwapBuffers( window );
        glfwPollEvents();
        data_write = 0;
        lk.unlock();
    }
    exit_thread = 1;
    aThread.join();

    glfwTerminate();
    return 0;
}

