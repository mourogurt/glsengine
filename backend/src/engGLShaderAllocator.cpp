#include "./include/engGLShaderAllocator.hpp"

EngGLShader::EngGLShader()
{
    program = gl::glCreateProgram();
}

EngGLShader::~EngGLShader()
{
    gl::glDeleteProgram(program);
}

gl::GLenum EngGLShader::compile (std::string str)
{

}

/*EngGLShaderAllocator::EngGLShaderAllocator()
{

}*/

