#include "engCamera.hpp"

glm::vec3 EngCamera::findCenter (const EngModel* model)
{
    size_t ixmin = 0,ixmax = 0,iymin = 0,iymax = 0,izmin = 0,izmax = 0;
    for (size_t i = 0; i < model->size_data; i+=3)
    {
        if (model->vertex_data[i] < model->vertex_data[ixmin]) ixmin = i;
        if (model->vertex_data[i] > model->vertex_data[ixmax]) ixmax = i;
        if (model->vertex_data[i+1] < model->vertex_data[iymin]) iymin = i+1;
        if (model->vertex_data[i+1] > model->vertex_data[iymax]) iymax = i+1;
        if (model->vertex_data[i+2] < model->vertex_data[izmin]) izmin = i+2;
        if (model->vertex_data[i+2] > model->vertex_data[izmax]) izmax = i+2;
    }
    glm::vec3 result;
    result[0] = (model->vertex_data[ixmin] + model->vertex_data[ixmax])/2.0f;
    result[1] = (model->vertex_data[iymin] + model->vertex_data[iymax])/2.0f;
    result[2] = (model->vertex_data[izmin] + model->vertex_data[izmax])/2.0f;
    return result;
}

glm::vec3 EngCamera::findCenter (EngModelArray* arr,int num)
{
    EngModel* model = arr->getModel(num);
    size_t ixmin = 0,ixmax = 0,iymin = 0,iymax = 0,izmin = 0,izmax = 0;
    for (size_t i = 0; i < model->size_data; i+=3)
    {
        if (model->vertex_data[i] < model->vertex_data[ixmin]) ixmin = i;
        if (model->vertex_data[i] > model->vertex_data[ixmax]) ixmax = i;
        if (model->vertex_data[i+1] < model->vertex_data[iymin]) iymin = i+1;
        if (model->vertex_data[i+1] > model->vertex_data[iymax]) iymax = i+1;
        if (model->vertex_data[i+2] < model->vertex_data[izmin]) izmin = i+2;
        if (model->vertex_data[i+2] > model->vertex_data[izmax]) izmax = i+2;
    }
    glm::vec3 result;
    result[0] = (model->vertex_data[ixmin] + model->vertex_data[ixmax])/2.0f;
    result[1] = (model->vertex_data[iymin] + model->vertex_data[iymax])/2.0f;
    result[2] = (model->vertex_data[izmin] + model->vertex_data[izmax])/2.0f;
    return result;
}
