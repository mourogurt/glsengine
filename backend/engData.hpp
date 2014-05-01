#ifndef ENGDATA_HPP
#define ENGDATA_HPP
#include "engInit.hpp"

class EngData
{
public:
    EngData();
    void setName (std::string);
    void setProgram (GLuint);
    virtual void setLength (GLuint lengthi) {length = lengthi;}
    virtual void setData(GLfloat* datai) { data = datai;}
    virtual void clear() { length = 0; data = nullptr; }
    virtual void bind()
    {
        location = glGetAttribLocation(program,name.c_str());
    }
    virtual void write()
    {
        if (length == 1)
            glVertexAttrib1fv(location,data); else
        if (length == 2)
            glVertexAttrib1fv(location,data); else
        if (length == 3)
            glVertexAttrib1fv(location,data); else
        if (length == 4)
            glVertexAttrib1fv(location,data);
    }
    ~EngData();
protected:
    GLuint program;
    std::string name;
    GLuint location;
private:
    GLfloat* data;
    GLuint length;
    GLuint VAO;
};

#endif // ENGDATA_HPP
