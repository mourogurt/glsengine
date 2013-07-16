#include "engModel.hpp"

EngModelArray::EngModelArray()
{
    models.clear();
}

void* EngModelArray::loadModel(EngLoadModelFunct funct, const char* pth)
{
    void* data = NULL;
    EngModel tmpmodel;
    tmpmodel = funct.func(data,pth);
    models.push_back(tmpmodel);
    return data;
}

void* EngModelArray::genModel(EngGenModelFunct funct, void* in)
{
    void* data = NULL;
    EngModel tmpmodel;
    tmpmodel = funct.func(data,in);
    models.push_back(tmpmodel);
    return data;
}

EngModel* EngModelArray::getModel(int n)
{
    return &(models[n]);
}

void EngModelArray::destroy()
{
    for (auto i = models.begin(); i < models.end(); i++)
    {
        if (i -> vertexBuffer != nullptr){ glDeleteBuffers(1, i -> vertexBuffer); delete [] i -> vertexBuffer; }
        if (i -> vertexID != nullptr){ glDeleteVertexArrays(1, i -> vertexID); delete [] i -> vertexID; }
        if (i -> vertex_data != nullptr) delete [] i -> vertex_data;
    }
    models.clear();
}
