#include "engData.hpp"

EngAttribute::EngAttribute()
{
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    length = 0;
    name = NULL;
    data = NULL;
}

void EngAttribute::setLength(GLuint lengthi)
{
    length = lengthi;
}

void EngAttribute::setData(GLfloat* datai)
{
    if (data != NULL)
        delete [] data;
    data = new GLfloat[length];
    memcpy(data,datai,length);
}

void EngAttribute::setName(char* namei)
{
    if (name != NULL)
        delete [] name;
    name = new char[strlen(namei)];
    strcpy(name,namei);
}

void EngAttribute::setProgram(GLuint programi)
{
    program = programi;
}

void EngAttribute::bind()
{
    location = glGetAttribLocation(program,name);
}

void EngAttribute::write()
{
    if (length == 1)
        glVertexAttrib1fv(location,data); else
    if (length == 2)
        glVertexAttrib2fv(location,data); else
    if (length == 3)
        glVertexAttrib3fv(location,data); else
    if (length == 4)
        glVertexAttrib4fv(location,data);
}

void EngAttribute::clear()
{
    length = 0;
    if (data != NULL)
        delete [] data;
    if (name != NULL)
        delete [] name;
}

EngAttribute::~EngAttribute()
{
    glDeleteVertexArrays(1,&VAO);
    if (name!=NULL)
        delete [] name;
    if (data!=NULL)
        delete [] data;
}
