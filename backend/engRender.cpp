#include "engRender.hpp"

EngRender::EngRender()
{
    props.thread_launched = 0;
    props.platform = nullptr;
    props.func_pre = nullptr;
    props.func_loop = nullptr;
    props.func_post = nullptr;
}

void EngRender::setPlatform(EngPlatform *platformin)
{
    props.platform = platformin;
}

void EngRender::setRenderFunction(unsigned int num,void* funcin)
{
    switch (num)
    {
    case 1:
        props.func_pre = (ENG_RENDER_FUNCTION_PRE_LOOP) funcin;
    case 2:
        props.func_loop = (ENG_RENDER_FUNCTION_LOOP) funcin;
    case 3:
        props.func_post = (ENG_RENDER_FUNCTION_POST_LOOP) funcin;
    }
}

void EngRender::setInData(Buffer* data)
{
    props.indata = data;
}

void EngRender::getOutData(std::vector<Buffer *> &data)
{
    Buffer* buf;
    while (props.outdata.size() > 0)
    {
        buf = props.outdata.pop();
        data.push_back(buf);
    }
}

void EngRender::stopRender()
{
    if (props.thread_launched)
    {
        props.thread_launched = 0;
        if (props.render_thread.joinable())
            props.render_thread.join();
    }
}

void EngRender::render()
{
    props.thread_launched = 1;
    props.render_thread = std::thread(thread_func,&props);
    glfwMakeContextCurrent(nullptr);
}

void thread_func (EngRenderData *render)
{
    Buffer *outpack = nullptr;
    Buffer *to_loop = nullptr;
    Buffer *to_post_pre = nullptr;
    Buffer *to_post_loop = nullptr;
    if (render->func_pre != nullptr)
    {
        render->func_pre(render->platform,render->indata, outpack, to_loop, to_post_pre);
    if (outpack != nullptr)
        render->outdata.push(outpack);
    }
    glfwMakeContextCurrent(render->platform->window);
    while ((render->thread_launched) && (!glfwWindowShouldClose(render->platform->window)))
    {
        if (render->func_loop != nullptr)
        {
            outpack = nullptr;
            render->func_loop(render->platform,render->indata,outpack,to_loop,to_post_loop);
            if (outpack != nullptr)
                render->outdata.push(outpack);
        }
        glfwSwapBuffers(render->platform ->window);
    }
    if (render->func_post != nullptr)
    {
        outpack = nullptr;
        render->func_post(render->platform,render->indata,outpack,to_post_pre,to_post_loop);
        if (outpack != nullptr)
            render->outdata.push(outpack);
    }
}
