#ifndef ENGMODEL_HPP
#define ENGMODEL_HPP
#include "engInit.hpp"

struct EngModel
{
    GLuint vertexID;
    GLuint vertexBuffer;
    GLfloat *vertex_data;
};

typedef EngModel (*ENG_LOAD_MODEL) (void*);

struct EngLoadModelFunct
{
    ENG_LOAD_MODEL func;
};

class EngModelArray
{
public:
    EngModelArray();
    void* loadModel(EngLoadModelFunct);
    EngModel* getModel(int);
    void clearArray();
private:
    std::vector<EngModel> models;
};

//typedef ()

#endif // ENGMODEL_HPP
