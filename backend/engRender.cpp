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

void EngRender::setController(ContextMutex *locker)
{
    props.current_controller = locker;
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
        props.current_controller->lock(props.platform->window);
    }
}

void EngRender::render()
{
    props.current_controller->unlock();
    props.thread_launched = 1;
    props.render_thread = std::thread(thread_func,&props);
}

void thread_func (EngRenderData *render)
{
    Buffer *outpack = new Buffer;
    outpack->buff = nullptr;
    Buffer *to_loop = new Buffer;
    to_loop->buff = nullptr;
    Buffer *to_post_pre = new Buffer;
    to_post_pre->buff = nullptr;
    Buffer *to_post_loop = new Buffer;
    to_post_loop->buff = nullptr;
    if (render->func_pre != nullptr)
    {
        render->current_controller->lock(render->platform->window);
        render->func_pre(render->platform,render->indata, outpack, to_loop, to_post_pre);
        render->current_controller->unlock();
    if (outpack->buff != nullptr)
        render->outdata.push(outpack);
    else
        delete [] outpack;
    }
    while ((render->thread_launched) && (!glfwWindowShouldClose(render->platform->window)))
    {
        if (render->func_loop != nullptr)
        {
            outpack = new Buffer;
            outpack->buff = nullptr;
            render->current_controller->lock(render->platform->window);
            render->func_loop(render->platform,render->indata,outpack,to_loop,to_post_loop);
            render->current_controller->unlock();
            if (outpack->buff != nullptr)
                render->outdata.push(outpack);
            else
                delete [] outpack;
        }
        glfwSwapBuffers(render->platform ->window);
    }
    if (render->func_post != nullptr)
    {
        outpack = new Buffer;
        outpack->buff = nullptr;
        render->current_controller->lock(render->platform->window);
        render->func_post(render->platform,render->indata,outpack,to_post_pre,to_post_loop);
        render->current_controller->unlock();
        if (outpack->buff != nullptr)
            render->outdata.push(outpack);
        else
            delete [] outpack;
    }
    if (to_loop != NULL)
    {
        if (to_loop->buff != nullptr)
            delete [] to_loop->buff;
        delete [] to_loop;
    }
    if (to_post_pre != NULL)
    {
        if (to_post_pre->buff != nullptr)
            delete [] to_post_pre->buff;
        delete [] to_post_pre;
    }
    if (to_post_loop != NULL)
    {
        if (to_post_loop->buff != nullptr)
            delete [] to_post_loop->buff;
        delete [] to_post_loop;
    }
}
