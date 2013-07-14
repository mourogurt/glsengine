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
