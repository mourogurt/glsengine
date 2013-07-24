#ifndef ENGCAMERA_HPP
#define ENGCAMERA_HPP
#include "engInit.hpp"
#include "engModel.hpp"
#include <glm/glm.hpp> // glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
using namespace glm;

class EngCamera
{
public:
    void init();
    void init(char*);
    void setVar(char*);
    void target(glm::vec3);
    void target(const EngModel*);
    void target(EngModelArray*,int);
    void move(glm::vec3);
    void setPerspective (GLfloat,GLfloat,GLfloat);
    void setLook(glm::mat4,bool);
    char* getVar();
    int getID;
private:
    glm::vec3 findCenter (const EngModel*);
    glm::vec3 findCenter (EngModelArray*,int);
    void setup();
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 mvp;
    GLuint matrixid;
    char* glslvar;
};


#endif // ENGCAMERA_HPP
