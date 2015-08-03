#ifndef ENGGLSHADERALLOCATOR_HPP
#define ENGGLSHADERALLOCATOR_HPP
#include <engInit.hpp>

class EngGLShader
{
public:
    EngGLShader();
    gl::GLenum compile (std::string);
    std::vector<std::string> getLog();
    std::vector<std::string> getErrLog();
    ~EngGLShader();
private:
    gl::GLenum type;
    GLuint program;
    Log log;
    Log errlog;

};

/*class EngGLShaderAllocator
{
public:
    EngGLShaderAllocator();
};*/

#endif // ENGGLSHADERALLOCATOR_HPP
