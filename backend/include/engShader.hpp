#ifndef ENGSHADER_HPP
#define ENGSHADER_HPP
#include <engInit.hpp>

class EngGLShader {
public:
  EngGLShader();
  GLuint compileShaderStage(GLuint, std::string&);
  GLuint linkShader();
  void cleanShader();
  void cleanProgram();
  void cleanShaderStage(GLuint);
  GLuint getProgramID();
  void bind_program();
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
  ~EngGLShader();
private:
  Log log;
  Log errlog;
  GLuint VStage;
  GLuint TCStage;
  GLuint TEStage;
  GLuint GStage;
  GLuint FStage;
  GLuint CStage;
  GLuint Program;
  static GLuint current_program;
};

#endif // ENGSHADER_HPP
