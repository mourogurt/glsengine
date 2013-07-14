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

EngModel* EngModelArray::getModel(int n)
{
    return &(models[n]);
}

void EngModelArray::Destroy()
{
    for (auto i = models.begin(); i < models.end(); i++)
    {
        if (i -> vertexBuffer != 0) glDeleteBuffers(1, &(i -> vertexBuffer));
        if (i -> vertexID != 0) glDeleteVertexArrays(1, &(i -> vertexID));
        if (i -> vertex_data != NULL) delete [] i -> vertex_data;
    }
    models.clear();
}
