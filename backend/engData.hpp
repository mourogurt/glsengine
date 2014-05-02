#ifndef ENGDATA_HPP
#define ENGDATA_HPP
#include "engInit.hpp"
#include <cstring>

class EngAttribute
{
public:
    EngAttribute();
    void setName (char*);
    void setProgram (GLuint);
    void setLength (GLuint);
    void setData(GLfloat*);
    void clear();
    void bind();
    void write();
    ~EngAttribute();
protected:
    GLuint program;
    char* name;
    GLint location;
private:
    GLfloat* data;
    GLuint length;
    GLuint VAO;
};

/*class EngAttributeArray : protected EngAttribute
{
public:
   //void bind();
   //void write();
   //void setLength(GLuint);
   //void setData(GLfloat*);
private:
   GLfloat* data;
   GLuint length;

};*/

#endif // ENGDATA_HPP
