#ifndef ENGVALUE_HPP
#define ENGVALUE_HPP
#include <engShader.hpp>
#include <cstring>
#include <typeinfo>

class EngGLAttribute {
public:
  EngGLAttribute(EngGLProgram*, GLint locationi = -1);
  EngGLAttribute(EngGLProgram*, std::string);
  bool setLocation(std::string);
  void setLocation(GLint);
  void setShader(EngGLProgram*);
  bool write(const GLfloat *, unsigned);
  bool write(const GLshort *, unsigned);
  bool write(const GLdouble *, unsigned);
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();

private:
  EngGLProgram* shader;
  GLint location;
  Log log;
  Log errlog;
};

class EngGLUniform {
public:
  EngGLUniform(EngGLProgram*, GLint locationi = -1);
  EngGLUniform(EngGLProgram*, std::string);
  bool setLocation(std::string);
  void setLocation(GLint);
  void setShader(EngGLProgram*);
  bool write(const GLfloat *, unsigned, GLsizei);
  bool write(const GLint *, unsigned, GLsizei);
  bool write(const GLuint *, unsigned, GLsizei);
  bool write(const GLfloat *, unsigned, unsigned, GLsizei,
             gl::GLboolean transpose = gl::GLboolean(GL_FALSE));
  bool write(const GLdouble *, unsigned, unsigned, GLsizei,
             gl::GLboolean transpose = gl::GLboolean(GL_FALSE));
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();

private:
  EngGLProgram* shader;
  GLint location;
  Log log;
  Log errlog;
};

#endif // ENGVALUE_HPP
