#include "engCamera.hpp"
#include <iostream>

void EngCamera::setVar(char * var,EngComputeArray* arr, size_t num)
{
    GLuint programID = arr->getProgram(num);
    matrixID = glGetUniformLocation(programID, var);
}

void EngCamera::setVar(char * var, GLuint programID)
{
    matrixID = glGetUniformLocation(programID, var);
}

void EngCamera::target(const EngModel * model)
{
    look = findCenter(model);
}

void EngCamera::target(EngModelArray *arr, int num)
{
    EngModel* model = arr->getModel(num);
    look = findCenter(model);
}

void EngCamera::target(glm::vec3 coords)
{
    look = coords;
}

void EngCamera::move(glm::vec3 coords)
{
    pos = coords;
}

void EngCamera::setPerspective(GLfloat fov, GLfloat near, GLfloat far,const EngPlatform* platform)
{
    proj = glm::perspective(fov,float(platform->width / platform->height),near,far);
}

void EngCamera::setLook(glm::mat4 modin, bool upside)
{
    model = modin;
    origin = upside;
}

void EngCamera::lookin()
{
    if (origin == false)
        view = glm::lookAt(pos,look,glm::vec3(0.0f,1.0f,0.0f));
    else
        view = glm::lookAt(pos,look,glm::vec3(0.0f,-1.0f,0.0f));
}

void EngCamera::writeVar()
{

    mvp = proj * view * model;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
}

GLuint EngCamera::getID()
{
    return matrixID;
}

glm::vec3 EngCamera::findCenter (const EngModel* model)
{
    size_t ixmin = 0,ixmax = 0,iymin = 1,iymax = 1,izmin = 2,izmax = 2;
    for (size_t i = 0; i < model->size_data-2; i+=3)
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
