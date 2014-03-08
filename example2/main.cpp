#include <iostream>
#include <fstream>
#include "engRender.hpp"
#include "engObject.hpp"

using namespace std;

void pre_render_func (const EngPlatform*,const Buffer*, Buffer*, Buffer*, Buffer*);
void loop_func (const EngPlatform*,const Buffer*, Buffer*, Buffer*, Buffer*);
void post_loop_func (const EngPlatform*,const Buffer*, Buffer*, Buffer*, Buffer*);

void key_callback(GLFWwindow*, int, int, int, int);

int main()
{
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f, 1.0f,
       1.0f, -1.0f, 0.0f, 1.0f,
       0.0f,  1.0f, 0.0f, 1.0f
    };
    std::string FragmentShaderCode;
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream("vertex.glsl");
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }
    std::ifstream FragmentShaderStream("fragment.glsl");
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }
    EngInit initclgl;
    EngRender render;
    EngObject object;
    initclgl.setHint({GLFW_CONTEXT_VERSION_MAJOR,3,GLFW_CONTEXT_VERSION_MINOR,3});
    initclgl.init("Example 2",800,640);
    initclgl.setCallback(KEYFUN,(void*)key_callback);
    initclgl.createContext(0);
    auto platform = initclgl.getEngPlatform(0);
    auto locker = initclgl.getLocker();
    render.setController(locker);
    render.setPlatform(platform);
    object.setController(locker);
    object.setPlatform(platform);
    object.init();
    render.setRenderFunction(ENGFUNCPRELOOP,(void*)pre_render_func);
    render.setRenderFunction(ENGFUNCLOOP,(void*)loop_func);
    render.setRenderFunction(ENGFUNCPOSTLOOP,(void*)post_loop_func);
    object.loadShader(VertexShaderCode,GL_VERTEX_SHADER);
    object.loadShader(FragmentShaderCode,GL_FRAGMENT_SHADER);
    object.createGPUShader();
    std::vector<std::string> errlog = object.getErrLog();
    for (unsigned int i = 0; i < errlog.size(); i++)
       cout<<errlog[i]<<endl;
    auto var_index = object.loadShaderVar("vertexPosition_modelspace");
    auto buf_index = object.loadData((void*)g_vertex_buffer_data,sizeof(g_vertex_buffer_data),var_index);
    object.createGPUData(buf_index);
    Buffer buf;
    buf.buff = (char*)&object;
    buf.buffsize = sizeof(EngObject);
    render.setInData(&buf);
    glFlush();
    render.render();
    while (!glfwWindowShouldClose(platform->render_window))
        glfwWaitEvents();
    render.stopRender();
    object.clearAll();
    initclgl.destroy();
    return 0;
}

void pre_render_func(const EngPlatform *platform,const Buffer *indata, Buffer *outdata, Buffer *to_loop, Buffer *to_post)
{
    /*static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f, 1.0f,
       1.0f, -1.0f, 0.0f, 1.0f,
       0.0f,  1.0f, 0.0f, 1.0f
    };
    EngObject* objin = (EngObject*) indata->buff;
    objin->createGPUShader();
    std::vector<std::string> errlog = objin->getErrLog();
    for (unsigned int i = 0; i < errlog.size(); i++)
       cout<<errlog[i]<<endl;
    auto var_index = objin->loadShaderVar("vertexPosition_modelspace");
    auto index = objin->loadData((void*)g_vertex_buffer_data,sizeof(g_vertex_buffer_data),var_index);
    objin->createGPUData(index);*/
    EngObject* objin = (EngObject*) indata->buff;
    objin->createVAO();
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void loop_func (const EngPlatform *platform,const Buffer *indata, Buffer *outdata, Buffer *from_pre, Buffer *to_post)
{
    glClear( GL_COLOR_BUFFER_BIT );
    EngObject* objin = (EngObject*) indata->buff;
    objin->render();
}

void post_loop_func (const EngPlatform *platform,const Buffer *indata, Buffer *outdata, Buffer *from_pre, Buffer *from_loop)
{
    EngObject* objin = (EngObject*) indata->buff;
    objin->removeVAO();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
