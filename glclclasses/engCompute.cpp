#include "engCompute.hpp"

EngComputeArray::EngComputeArray()
{
    sources.clear();
    programs.clear();
    log.clearLog();
    errlog.clearLog();
}

void* EngComputeArray::addCompute(EngLoadCompFunct funct, void *in)
{
    EngCompute tmp;
    void* out = nullptr;
    tmp = funct.func(in,out);
    sources.push_back(tmp);
    return out;
}

GLuint EngComputeArray::createProgram(int num, int &err)
{

}

