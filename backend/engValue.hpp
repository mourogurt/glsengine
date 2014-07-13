#ifndef ENGVALUE_HPP
#define ENGVALUE_HPP
#include "engInit.hpp"
#include <cstring>
#include <typeinfo>

class EngGLAttribute
{
public:
    bool bind(std::string);
    void bind(GLint);
    void setProgram(GLuint);
    bool write(const GLfloat*, unsigned);
    bool write(const GLshort*, unsigned);
    bool write(const GLdouble*, unsigned);
    std::vector<std::string> getLog();
    std::vector<std::string> getErrLog();
private:
    GLuint program;
    GLint location;
    Log log;
    Log errlog;
};

#endif // ENGVALUE_HPP
