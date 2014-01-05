#include "engRender.hpp"

EngRender::EngRender()
{
    props.thread_launched = 0;
    props.platform = nullptr;
    props.func = nullptr;
}

void EngRender::setPlatform(EngPlatform *platformin)
{
    props.platform = platformin;
}

void EngRender::setRenderFunction(ENG_RENDER_FUNCTION funcin)
{
    props.func = funcin;
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
    Buffer *outpack;
    glfwMakeContextCurrent(render->platform->window);
    while ((render->thread_launched) && (!glfwWindowShouldClose(render->platform->window)))
    {
        outpack = nullptr;
        render->func(render->platform,render->indata,outpack);
        if (outpack != nullptr)
            render->outdata.push(outpack);
        glfwSwapBuffers(render->platform ->window);
    }
}
