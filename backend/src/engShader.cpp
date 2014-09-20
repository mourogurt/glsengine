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

GLuint EngGLShader::compileShaderStage(GLuint stage, std::string &source) {
    if ((stage != GL_VERTEX_SHADER) && (stage != GL_TESS_CONTROL_SHADER)
         && (stage != GL_TESS_EVALUATION_SHADER) && (stage != GL_GEOMETRY_SHADER)
         && (stage != GL_FRAGMENT_SHADER) && (stage != GL_COMPUTE_SHADER))
    {
        dlog("Add errlog");
        errlog.writeLog("Unknown shader stage");
        return GL_FALSE;
    }
    cleanShaderStage(stage);
    GLuint cur_stage = glCreateShader(stage);
    char const *source_pointer = source.c_str();
    glShaderSource(cur_stage, 1, &source_pointer, NULL);
    glCompileShader(cur_stage);
    {
      GLint result;
      glGetShaderiv(cur_stage, GL_COMPILE_STATUS, &result);
      if (result == GL_FALSE) {
        GLsizei lengthmsg;
        glGetShaderiv(cur_stage, GL_INFO_LOG_LENGTH, &lengthmsg);
        GLchar *logmsg[lengthmsg];
        glGetShaderInfoLog(cur_stage, lengthmsg, NULL, (GLchar *)logmsg);
        glDeleteShader(cur_stage);
        dlog("Add errlog");
        errlog.writeLog(std::string((const char *)logmsg));
        return result;
      }
    }
    switch (stage) {
    case GL_VERTEX_SHADER:
        if (VStage != 0) cleanShaderStage(VStage); VStage = cur_stage; break;
    case GL_TESS_CONTROL_SHADER:
        if (VStage != 0) cleanShaderStage(TCStage); TCStage = cur_stage; break;
    case GL_TESS_EVALUATION_SHADER:
        if (VStage != 0) cleanShaderStage(TEStage); TEStage = cur_stage; break;
    case GL_GEOMETRY_SHADER:
        if (VStage != 0) cleanShaderStage(GStage); GStage = cur_stage; break;
    case GL_FRAGMENT_SHADER:
        if (VStage != 0) cleanShaderStage(FStage); FStage = cur_stage; break;
    case GL_COMPUTE_SHADER:
        if (CStage != 0) cleanShaderStage(CStage); CStage = cur_stage; break;
    };
  dlog("compileShaderStage(GLuint,std::string) OK");
  return GL_TRUE;
}

GLuint EngGLShader::linkShader() {
  if (Program != 0)
    cleanProgram();
  Program = glCreateProgram();
  if (VStage != 0)
    glAttachShader(Program, VStage);
  if (TCStage != 0)
    glAttachShader(Program, TCStage);
  if (TEStage != 0)
    glAttachShader(Program, TEStage);
  if (GStage != 0)
    glAttachShader(Program, GStage);
  if (FStage != 0)
    glAttachShader(Program, FStage);
  if (CStage != 0)
    glAttachShader(Program, CStage);
  glLinkProgram(Program);
  {
    GLint result;
    glGetProgramiv(Program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
      GLsizei lengthmsg;
      glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &lengthmsg);
      GLchar *logmsg[lengthmsg];
      glGetShaderInfoLog(Program, lengthmsg, NULL, (GLchar *)logmsg);
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
    cleanShaderStage(GL_COMPUTE_SHADER);
  if (FStage != 0)
    cleanShaderStage(GL_FRAGMENT_SHADER);
  if (GStage != 0)
    cleanShaderStage(GL_GEOMETRY_SHADER);
  if (TEStage != 0)
    cleanShaderStage(GL_TESS_EVALUATION_SHADER);
  if (TCStage != 0)
    cleanShaderStage(GL_TESS_CONTROL_SHADER);
  if (VStage != 0)
    cleanShaderStage(GL_VERTEX_SHADER);
}

void EngGLShader::cleanProgram() {
  glDeleteProgram(Program);
  Program = 0;
}

void EngGLShader::cleanShaderStage(GLuint stage) {
  if (stage == GL_COMPUTE_SHADER) {
    glDeleteShader(CStage);
    CStage = 0;
  } else if (stage == GL_FRAGMENT_SHADER) {
    glDeleteShader(FStage);
    FStage = 0;
  } else if (stage == GL_GEOMETRY_SHADER) {
    glDeleteShader(GStage);
    GStage = 0;
  } else if (stage == GL_TESS_EVALUATION_SHADER) {
    glDeleteShader(TEStage);
    TEStage = 0;
  } else if (stage == GL_TESS_CONTROL_SHADER) {
    glDeleteShader(TCStage);
    TCStage = 0;
  } else if (stage == GL_VERTEX_SHADER) {
    glDeleteShader(VStage);
    VStage = 0;
  }
}

GLuint EngGLShader::getProgramID() { return Program; }

void EngGLShader::bind_program()
{
    if (current_program != Program)
    {
        current_program = Program;
        glUseProgram(Program);
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
        glUseProgram(0);
    }
    cleanShader();
}
