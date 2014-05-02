#ifndef ENGDATA_HPP
#define ENGDATA_HPP
#include "engInit.hpp"
#include <cstring>

class EngGLData
{
public:
    EngGLData();
    void setName (const char*);
    void setProgram (GLuint);
    void setLength (GLuint);
    virtual void clear() = 0;
    virtual void bind() = 0;
    virtual void write(const GLfloat*) = 0;
    std::vector<std::string> getLog();
    std::vector<std::string> getErrLog();
    ~EngGLData();
protected:
    char* name;
    GLuint program;
    GLuint length;
    Log log;
    Log errlog;
private:
    GLuint VAO;

};

class EngAttribute: public EngGLData
{
public:
    void clear();
    void bind();
    void write(const GLfloat*);
private:
    GLint location;
};

#endif // ENGDATA_HPP
