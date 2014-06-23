#ifndef ENGDATA_HPP
#define ENGDATA_HPP
#include "engInit.hpp"
#include <cstring>
#include <typeinfo>

class EngGLvalue
{
public:
    EngGLvalue();
    void setName (const char*);
    void setProgram (GLuint);
    void setLength (GLuint);
    virtual void clear() = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;
    std::vector<std::string> getLog();
    std::vector<std::string> getErrLog();
    ~EngGLvalue();
protected:
    char* name;
    GLuint program;
    GLuint length;
    Log log;
    Log errlog;
private:
    GLuint VAO;

};

class EngGLbuffer
{
public:
    EngGLbuffer();
    ~EngGLbuffer();
};

class EngAttribute final: public EngGLvalue
{
public:
    void clear();
    void bind();
    void unbind();
    bool write(const GLfloat*);
    bool write(const GLshort*);
    bool write(const GLdouble*);
private:
    GLint location;
};

#endif // ENGDATA_HPP
