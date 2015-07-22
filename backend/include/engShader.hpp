#ifndef ENGSHADER_HPP
#define ENGSHADER_HPP
#include <engInit.hpp>

class EngGLProgram {
public:
  EngGLProgram();
  GLuint compileShaderStage(gl::GLenum, const std::string&);
  void setSeparable (gl::GLint);
  void setCacheable (gl::GLint);
  void createProgram();
  GLuint linkShader();
  void saveBinary (std::string&, gl::GLenum&);
  void loadBinary (const std::string&, const gl::GLenum&);
  void cleanShader();
  void cleanProgram();
  void cleanShaderStage(gl::GLenum);
  GLuint getProgramID();
  void bind_program();
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
  ~EngGLProgram();
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
  gl::GLint separable;
  gl::GLint cacheable;
  static GLuint current_program;
};

class EngGLPipeline
{
public:
    EngGLPipeline();
    unsigned createProgam();
    EngGLProgram* getProgram(unsigned);
    void useProgram(unsigned,gl::UseProgramStageMask);
    void bindPipeline();
    void removeProgram(unsigned);
    void clean();
    ~EngGLPipeline();
private:
    std::vector<EngGLProgram*> programs;
    std::queue<unsigned> to_delete;
    gl::GLuint pipeline;
    //static gl::GLuint current_pipeline;
};

#endif // ENGSHADER_HPP
