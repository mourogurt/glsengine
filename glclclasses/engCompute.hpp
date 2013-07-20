#ifndef ENGCOMPUTE_HPP
#define ENGCOMPUTE_HPP
#include "engInit.hpp"

struct EngCompute
{
    char* vertex_source;
    char* fragment_source;
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
    void* addCompute(EngLoadCompFunct,void*);
    GLuint createProgram(int,int&);
    void destroy();
    std::vector<const char*> getLog();
    std::vector<const char*> getErrLog();
    void clearLog();
    void clearErrLog();
private:
    std::vector<EngCompute> sources;
    std::vector<GLuint> programs;
    EngLog log;
    EngLog errlog;
};

#endif // ENGCOMPUTE_HPP
