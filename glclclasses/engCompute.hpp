#ifndef ENGCOMPUTE_HPP
#define ENGCOMPUTE_HPP
#include "engInit.hpp"

struct EngCompute
{
    char* vertex_source;
    char* fraagment_source;
};

typedef EngCompute (*ENGLOADCOMPFUNC)(void*,void*);

struct EngLoadCompFunct
{
    ENGLOADCOMPFUNC func;
};

class EngComputeArray
{
public:
    EngComputeArray();
    EngCompute addCompute(EngLoadCompFunct,void*,void*);
    GLuint createProgram(int,int&);
    void Destroy();
    std::vector<const char*> GetLog();
    std::vector<const char*> GetErrLog();
    void ClearLog();
    void ClearErrLog();
private:
    std::vector<EngCompute> sources;
    std::vector<GLuint> programs;
    EngLog log;
    EngLog errlog;
};

#endif // ENGCOMPUTE_HPP
