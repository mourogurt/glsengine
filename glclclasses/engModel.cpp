#include "engModel.hpp"

EngModelArray::EngModelArray()
{
    models.clear();
}

void* EngModelArray::loadModel(EngLoadModelFunct funct)
{
    void* data;
    EngModel tmpmodel;
    tmpmodel = funct.func(data);
    models.push_back(tmpmodel);
    return data;
}

EngModel* EngModelArray::getModel(int n)
{
    return &(models[n]);
}

void EngModelArray::clearArray()
{
    for (auto i = models.begin(); i < models.end(); i++)
    {
        if (i -> vertexBuffer != 0) glDeleteBuffers(1, &(i -> vertexBuffer));
        if (i -> vertexID != 0) glDeleteVertexArrays(1, &(i -> vertexID));
    }
    models.clear();
}
