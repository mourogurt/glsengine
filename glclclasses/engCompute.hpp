#ifndef ENGCOMPUTE_HPP
#define ENGCOMPUTE_HPP
#include "engInit.hpp"
#include <deque>

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
    void deleteCompute(size_t);
    size_t getNumSources();
    size_t getNumPrograms();
    GLuint createProgram(int,int& = nullptr);
    void destroy();
    std::vector<const char*> getLog();
    std::vector<const char*> getErrLog();
    void clearLog();
    void clearErrLog();
private:
    void clearSource (int);
    std::deque<EngCompute> sources;
    std::vector<GLuint> programs;
    EngLog log;
    EngLog errlog;
};

#endif // ENGCOMPUTE_HPP
