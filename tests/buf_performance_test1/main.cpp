#include <iostream>
#include <fstream>
#include <engInit.hpp>
#include <engCustomShader.hpp>
#include <engBuffer.hpp>
#include <thread>
#include <ctime>
#include <cstdlib>
using namespace std;

bool ext;
bool data_write;
condition_variable cv;
mutex cv_m;

void gen_function(float*,unsigned);
void gen_function2(float*,unsigned);

double do_sub_buf(unsigned,unsigned,GLFWwindow*&,EngVBO&);
double do_map_buf_sync(unsigned,unsigned,GLFWwindow*&,EngVBO&);
double do_map_buf(unsigned,unsigned,GLFWwindow*&,EngVBO&);

int main()
{
    EngInit initgl;
    unsigned win1 = initgl.createGLWindow("perf test1",800,600);
    EngGLPlatform* platform = initgl.getEngGLPlatform(win1);
    glfwSetInputMode(platform->controll_window, GLFW_STICKY_KEYS, GL_TRUE);
    EngCustomShader shader;
    string src;
    ifstream in("vert.glsl");
    getline(in,src,'\0');
    in.close();
    shader.compileShaderStage(GL_VERTEX_SHADER,src);
    in.open("frag.glsl");
    getline(in,src,'\0');
    in.close();
    shader.compileShaderStage(GL_FRAGMENT_SHADER,src);
    shader.linkShader();
    auto log = shader.getErrLog();
    for (unsigned i = 0; i < log.size(); i++)
        cout << log[i]<<endl;
    if (log.size() > 0) return 1;
    GLuint program = shader.getProgramID();
    unsigned VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    EngVBO buf1;
    buf1.setLocation("position",program);
    buf1.enable();
    buf1.bind(3);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glUseProgram(program);
    ofstream out("output.txt",ios::trunc);
    unsigned frames_count[] = {100,500,1000};
    unsigned buf_count[] = {100,500,1000,1500,3000,3500,4000,5000,6000,10000,30000,100000,300000,600000,900000,1200000,1500000};
    for (unsigned i = 0; i < sizeof(frames_count)/sizeof(float); i++)
        for (unsigned j = 0; j < sizeof(buf_count)/sizeof(float); j++)
        {
            double res[3];
            res[0] = do_sub_buf(frames_count[i],buf_count[j],platform->controll_window,buf1);
            res[1] = do_map_buf_sync(frames_count[i],buf_count[j],platform->controll_window,buf1);
            res[2] = do_map_buf(frames_count[i],buf_count[j],platform->controll_window,buf1);
            out << "Sub buffer test: frames=" << frames_count[i]
                << "   buffer size=" << buf_count[j] << "   "
                << res[0] << endl;
            out << "Map buffer sync test: frames=" << frames_count[i]
                << "   buffer size=" << buf_count[j] << "   "
                << res[1] << endl;
            out << "Map buffer test: frames=" << frames_count[i]
                << "   buffer size=" << buf_count[j] << "   "
                << res[2] << endl;
            unsigned char min = 0;
            if(res[0] > res[1]) min = 1; else min = 0;
            if (res[min] > res[2]) min = 2;
            if (min == 0) out << "Min: Sub buffer\n\n";
            if (min == 1) out << "Min: Map buffer sync\n\n";
            if (min == 2) out << "Min: Map buffer\n\n";
        }
    out.close();
    buf1.clear();
    glDeleteVertexArrays(1,&VAO);
    return 0;
}

void gen_function(float *data, unsigned count)
{
    srand(time(NULL));
    while (!ext)
    {
        for (unsigned i = 0; i < (count/3)*3; i+=3)
        {
            data[i] = ((rand() % 2001) * 0.001f) - 1.0f;
            data[i+1] = ((rand() % 2001) * 0.001f) - 1.0f;
            data[i+2] = 0.0f;
        }
        data_write = 1;
        cv.notify_one();
    }
}

void gen_function2(float *data, unsigned count)
{
    srand(time(NULL));
    while (!ext)
    {
        for (unsigned i = 0; i < (count/3)*3; i+=3)
        {
            data[i] = ((rand() % 2001) * 0.001f) - 1.0f;
            data[i+1] = ((rand() % 2001) * 0.001f) - 1.0f;
            data[i+2] = 0.0f;
        }
    }
}

double do_sub_buf(unsigned frames, unsigned count, GLFWwindow* &win, EngVBO &buffer)
{
    buffer.allocate(count*sizeof(float),GL_DYNAMIC_DRAW);
    ext = 0;
    data_write = 0;
    float* buf = new float[count];
    double lastTime = glfwGetTime();
    thread mythread = thread(gen_function,buf,count);
    for (unsigned i = 0; i < frames; i++)
    {
        std::unique_lock<std::mutex> lk(cv_m);
        cv.wait(lk, [](){return data_write == 1;});
        buffer.write(buf,count*sizeof(float));
        glClear(GL_COLOR_BUFFER_BIT);
        buffer.render(count/3,0,GL_POINTS);
        glfwSwapBuffers(win);
        glfwPollEvents();
        data_write = 0;
        lk.unlock();
    }
    double currentTime = glfwGetTime();
    ext = 1;
    mythread.join();
    delete [] buf;
    buffer.clear();
    return currentTime - lastTime;
}

double do_map_buf_sync(unsigned frames, unsigned count, GLFWwindow* &win, EngVBO &buffer)
{
    buffer.allocate(count*sizeof(float),GL_DYNAMIC_DRAW);
    void* ptr = buffer.get_ptr();
    ext = 0;
    data_write = 0;
    double lastTime = glfwGetTime();
    thread mythread = thread(gen_function,(float*)ptr,count);
    for (unsigned i = 0; i < frames; i++)
    {
        std::unique_lock<std::mutex> lk(cv_m);
        cv.wait(lk, [](){return data_write == 1;});
        glClear(GL_COLOR_BUFFER_BIT);
        buffer.render(count/3,0,GL_POINTS);
        glfwSwapBuffers(win);
        glfwPollEvents();
        data_write = 0;
        lk.unlock();
    }
    double currentTime = glfwGetTime();
    ext = 1;
    mythread.join();
    buffer.clear();
    return currentTime - lastTime;
}

double do_map_buf(unsigned frames, unsigned count, GLFWwindow* &win, EngVBO &buffer)
{
    buffer.allocate(count*sizeof(float),GL_DYNAMIC_DRAW);
    void* ptr = buffer.get_ptr(GL_WRITE_ONLY | GL_MAP_UNSYNCHRONIZED_BIT);
    ext = 0;
    data_write = 0;
    double lastTime = glfwGetTime();
    thread mythread = thread(gen_function2,(float*)ptr,count);
    for (unsigned i = 0; i < frames; i++)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        buffer.render(count/3,0,GL_POINTS);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    double currentTime = glfwGetTime();
    ext = 1;
    mythread.join();
    buffer.clear();
    return currentTime - lastTime;
}
