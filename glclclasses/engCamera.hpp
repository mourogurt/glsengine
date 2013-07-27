#ifndef ENGCAMERA_HPP
#define ENGCAMERA_HPP
#include "engInit.hpp"
#include "engModel.hpp"
#include "engCompute.hpp"
#include <glm/glm.hpp> // glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class EngCamera
{
public:
    void setVar(char*,EngComputeArray*,size_t);
    void setVar(char *, GLuint);
    void target(glm::vec3);
    void target(const EngModel*);
    void target(EngModelArray*,int);
    void move(glm::vec3);
    void setPerspective (GLfloat,GLfloat,GLfloat,const EngPlatform*);
    void setLook(glm::mat4,bool);
    void lookin();
    void writeVar();
    GLuint getID();
private:
    glm::vec3 findCenter (const EngModel*);
    glm::vec3 pos;
    glm::vec3 look;
    bool origin;
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 mvp;
    GLuint matrixID;
    char* glslvar;
};


#endif // ENGCAMERA_HPP
