#include "engShader.hpp"
#include <string>

GLuint EngGLShader::current_program = 0;

EngGLShader::EngGLShader() {
  VStage = 0;
  TCStage = 0;
  TEStage = 0;
  GStage = 0;
  FStage = 0;
  CStage = 0;
  Program = 0;
}

GLuint EngGLShader::compileShaderStage(gl::GLenum stage, std::string &source) {
    if ((stage != GL_VERTEX_SHADER) && (stage != GL_TESS_CONTROL_SHADER)
         && (stage != GL_TESS_EVALUATION_SHADER) && (stage != GL_GEOMETRY_SHADER)
         && (stage != GL_FRAGMENT_SHADER) && (stage != GL_COMPUTE_SHADER))
    {
        dlog("Add errlog");
        errlog.writeLog("Unknown shader stage");
        return GL_FALSE;
    }
    cleanShaderStage(stage);
    GLuint cur_stage = gl::glCreateShader(stage);
    char const *source_pointer = source.c_str();
    gl::glShaderSource(cur_stage, 1, &source_pointer, NULL);
    gl::glCompileShader(cur_stage);
    {
      GLint result;
      gl::glGetShaderiv(cur_stage, gl::GLenum(GL_COMPILE_STATUS), &result);
      if (result == GL_FALSE) {
        GLsizei lengthmsg;
        gl::glGetShaderiv(cur_stage, gl::GLenum(GL_INFO_LOG_LENGTH), &lengthmsg);
        GLchar *logmsg[lengthmsg];
        gl::glGetShaderInfoLog(cur_stage, lengthmsg, NULL, (GLchar *)logmsg);
        gl::glDeleteShader(cur_stage);
        dlog("Add errlog");
        errlog.writeLog(std::string((const char *)logmsg));
        return result;
      }
    }
    switch (stage) {
    case gl::GLenum(GL_VERTEX_SHADER):
        if (VStage != 0) cleanShaderStage(gl::GLenum(GL_VERTEX_SHADER)); VStage = cur_stage; break;
    case gl::GLenum(GL_TESS_CONTROL_SHADER):
        if (TCStage != 0) cleanShaderStage(gl::GLenum(GL_TESS_CONTROL_SHADER)); TCStage = cur_stage; break;
    case gl::GLenum(GL_TESS_EVALUATION_SHADER):
        if (TEStage != 0) cleanShaderStage(gl::GLenum(GL_TESS_EVALUATION_SHADER)); TEStage = cur_stage; break;
    case gl::GLenum(GL_GEOMETRY_SHADER):
        if (GStage != 0) cleanShaderStage(gl::GLenum(GL_GEOMETRY_SHADER)); GStage = cur_stage; break;
    case gl::GLenum(GL_FRAGMENT_SHADER):
        if (FStage != 0) cleanShaderStage(gl::GLenum(GL_FRAGMENT_SHADER)); FStage = cur_stage; break;
    case gl::GLenum(GL_COMPUTE_SHADER):
        if (CStage != 0) cleanShaderStage(gl::GLenum(GL_COMPUTE_SHADER)); CStage = cur_stage; break;
    default:
        dlog("Add errlog");
        errlog.writeLog("Wrong stage");
        return GL_FALSE;
    };
  dlog("compileShaderStage(GLuint,std::string) OK");
  return GL_TRUE;
}

GLuint EngGLShader::linkShader() {
  if (Program != 0)
    cleanProgram();
  Program = gl::glCreateProgram();
  if (VStage != 0)
    gl::glAttachShader(Program, VStage);
  if (TCStage != 0)
    gl::glAttachShader(Program, TCStage);
  if (TEStage != 0)
    gl::glAttachShader(Program, TEStage);
  if (GStage != 0)
    gl::glAttachShader(Program, GStage);
  if (FStage != 0)
    gl::glAttachShader(Program, FStage);
  if (CStage != 0)
    gl::glAttachShader(Program, CStage);
  gl::glLinkProgram(Program);
  {
    GLint result;
    gl::glGetProgramiv(Program, gl::GLenum(GL_LINK_STATUS), &result);
    if (result == GL_FALSE) {
      GLsizei lengthmsg;
      gl::glGetProgramiv(Program, gl::GLenum(GL_INFO_LOG_LENGTH), &lengthmsg);
      GLchar *logmsg[lengthmsg];
      gl::glGetShaderInfoLog(Program, lengthmsg, NULL, (GLchar *)logmsg);
      cleanProgram();
#ifdef _DEBUG
      log.writeLog(std::string("Add errlog"));
#endif
      errlog.writeLog(std::string((const char *)logmsg));
      return GL_FALSE;
    }
  }
#ifdef _DEBUG
  log.writeLog(std::string("linkShader() OK"));
#endif
  return GL_TRUE;
}

void EngGLShader::cleanShader() {
  if (Program != 0)
    cleanProgram();
  if (CStage != 0)
    cleanShaderStage(gl::GLenum(GL_COMPUTE_SHADER));
  if (FStage != 0)
    cleanShaderStage(gl::GLenum(GL_FRAGMENT_SHADER));
  if (GStage != 0)
    cleanShaderStage(gl::GLenum(GL_GEOMETRY_SHADER));
  if (TEStage != 0)
    cleanShaderStage(gl::GLenum(GL_TESS_EVALUATION_SHADER));
  if (TCStage != 0)
    cleanShaderStage(gl::GLenum(GL_TESS_CONTROL_SHADER));
  if (VStage != 0)
    cleanShaderStage(gl::GLenum(GL_VERTEX_SHADER));
}

void EngGLShader::cleanProgram() {
  gl::glDeleteProgram(Program);
  Program = 0;
}

void EngGLShader::cleanShaderStage(gl::GLenum stage) {
  if (stage == GL_COMPUTE_SHADER) {
    gl::glDeleteShader(CStage);
    CStage = 0;
  } else if (stage == GL_FRAGMENT_SHADER) {
    gl::glDeleteShader(FStage);
    FStage = 0;
  } else if (stage == GL_GEOMETRY_SHADER) {
    gl::glDeleteShader(GStage);
    GStage = 0;
  } else if (stage == GL_TESS_EVALUATION_SHADER) {
    gl::glDeleteShader(TEStage);
    TEStage = 0;
  } else if (stage == GL_TESS_CONTROL_SHADER) {
    gl::glDeleteShader(TCStage);
    TCStage = 0;
  } else if (stage == GL_VERTEX_SHADER) {
    gl::glDeleteShader(VStage);
    VStage = 0;
  }
}

GLuint EngGLShader::getProgramID() { return Program; }

void EngGLShader::bind_program()
{
    if (current_program != Program)
    {
        current_program = Program;
        gl::glUseProgram(Program);
    }
}

std::vector<std::string> EngGLShader::getLog() { return log.getLog(); }

std::vector<std::string> EngGLShader::getErrLog() {
  return errlog.getLog();
}

EngGLShader::~EngGLShader()
{
    if (current_program == Program)
    {
        current_program = 0;
        gl::glUseProgram(0);
    }
    cleanShader();
}
