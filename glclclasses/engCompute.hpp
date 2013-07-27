#ifndef ENGCOMPUTE_HPP
#define ENGCOMPUTE_HPP
#include "engInit.hpp"
#include <deque>
#include <string>

struct EngCompute
{
    std::string vertex_source;
    std::string fragment_source;
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
    void deleteProgram (size_t);
    size_t getNumSources();
    size_t getNumPrograms();
    GLuint getProgram(int);
    int createProgram(int);
    void destroy();
    std::vector<const char*> getLog();
    std::vector<const char*> getErrLog();
    void clearLog();
    void clearErrLog();
private:
    void clearProgram (int);
    std::deque<EngCompute> sources;
    std::deque<GLuint> programs;
    EngLog log;
    EngLog errlog;
};

#endif // ENGCOMPUTE_HPP
