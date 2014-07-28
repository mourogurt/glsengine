#ifndef ENGVALUE_HPP
#define ENGVALUE_HPP
#include <engShader.hpp>
#include <cstring>
#include <typeinfo>

class EngGLAttribute {
public:
  bool bind(std::string);
  void bind(GLint);
  void setShader(EngShader*);
  bool write(const GLfloat *, unsigned);
  bool write(const GLshort *, unsigned);
  bool write(const GLdouble *, unsigned);
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();

private:
  EngShader* shader;
  GLint location;
  Log log;
  Log errlog;
};

class EngGLUniform {
public:
  bool bind(std::string);
  void bind(GLint);
  void setShader(EngShader*);
  bool write(const GLfloat *, unsigned, GLsizei);
  bool write(const GLint *, unsigned, GLsizei);
  bool write(const GLuint *, unsigned, GLsizei);
  bool write(const GLfloat *, unsigned, unsigned, GLsizei,
             GLboolean transpose = GL_FALSE);
  bool write(const GLdouble *, unsigned, unsigned, GLsizei,
             GLboolean transpose = GL_FALSE);
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();

private:
  EngShader* shader;
  GLint location;
  Log log;
  Log errlog;
};

#endif // ENGVALUE_HPP
