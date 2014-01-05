#ifndef ENGRENDER_H
#define ENGRENDER_H
#include <thread>
#include <vector>
#include "engInit.hpp"
#include "../system/log.h"

typedef void (*ENG_RENDER_FUNCTION)(const EngPlatform *, void *, void *);

struct EngRenderData
{
    std::thread render_thread;
    bool thread_launched;
    EngPlatform* platform;
    ENG_RENDER_FUNCTION func;
    Buffer* indata;
    ConcurentQueue outdata;
};

class EngRender
{
public:
    EngRender();
    void render();
    void setPlatform (EngPlatform*);
    void setRenderFunction(ENG_RENDER_FUNCTION);
    void setInData (Buffer*);
    void stopRender();
    void getOutData(std::vector<Buffer*>&);
private:
    EngRenderData props;
};

void thread_func(EngRenderData*);

#endif // ENGRENDER_H
