#ifndef ENGSHADER_HPP
#define ENGSHADER_HPP
#include <engInit.hpp>

class EngGLShader {
public:
  EngGLShader();
  GLuint compileShaderStage(gl::GLenum, std::string&);
  GLuint linkShader();
  void cleanShader();
  void cleanProgram();
  void cleanShaderStage(gl::GLenum);
  GLuint getProgramID();
  void bind_program();
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
  ~EngGLShader();
private:
  Log log;
  Log errlog;
  gl::GLuint VStage;
  gl::GLuint TCStage;
  gl::GLuint TEStage;
  gl::GLuint GStage;
  gl::GLuint FStage;
  gl::GLuint CStage;
  gl::GLuint Program;
  static GLuint current_program;
};

#endif // ENGSHADER_HPP
