#ifndef ENGMODEL_HPP
#define ENGMODEL_HPP
#include "engInit.hpp"

struct EngModel
{
    GLuint *vertexID;
    GLuint *vertexBuffer;
    GLfloat *vertex_data;
    GLuint size_data;
};

typedef EngModel (*ENG_LOAD_MODEL) (void*, const char*);
typedef EngModel (*ENG_GEN_MODEL) (void*,void*);

struct EngLoadModelFunct
{
    ENG_LOAD_MODEL func;
};

struct EngGenModelFunct
{
    ENG_GEN_MODEL func;
};

class EngModelArray
{
public:
    EngModelArray();
    void* loadModel(EngLoadModelFunct, const char*);
    void* genModel(EngGenModelFunct,void*);
    size_t getNumModels ();
    EngModel* getModel(int);
    void destroy();
    std::vector<const char*> getLog();
    void clearLog();
private:
    std::vector<EngModel> models;
    EngLog log;
};

//typedef ()

#endif // ENGMODEL_HPP
