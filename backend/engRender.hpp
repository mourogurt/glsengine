#ifndef ENGRENDER_H
#define ENGRENDER_H
#include <thread>
#include <vector>
#include "engInit.hpp"
#include "../system/log.h"

typedef void (*ENG_RENDER_FUNCTION_PRE_LOOP) (const EngPlatform *,const Buffer *, Buffer *, Buffer *, Buffer *);
typedef void (*ENG_RENDER_FUNCTION_LOOP)(const EngPlatform *,const Buffer *,Buffer *, Buffer *, Buffer *);
typedef void (*ENG_RENDER_FUNCTION_POST_LOOP) (const EngPlatform *,const Buffer *,Buffer *,Buffer *, Buffer *);

#define ENGFUNCPRELOOP 1
#define ENGFUNCLOOP 2
#define ENGFUNCPOSTLOOP 3

struct EngRenderData
{
    std::thread render_thread;
    bool thread_launched;
    EngPlatform* platform;
    ENG_RENDER_FUNCTION_PRE_LOOP func_pre;
    ENG_RENDER_FUNCTION_LOOP func_loop;
    ENG_RENDER_FUNCTION_POST_LOOP func_post;
    Buffer* indata;
    ConcurentQueue outdata;
    EngContextThreads* current_controller;
};

class EngRender
{
public:
    EngRender();
    void render();
    void setPlatform (EngPlatform*);
    void setContextController(EngContextThreads*);
    void setRenderFunction(unsigned int,void*);
    void setInData (Buffer*);
    void stopRender();
    void getOutData(std::vector<Buffer*>&);
private:
    EngRenderData props;

};

void thread_func(EngRenderData*);

#endif // ENGRENDER_H
