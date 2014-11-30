#include "engValue.hpp"

EngGLAttribute::EngGLAttribute(EngGLShader* shaderi, GLint locationi)
{
    shader = shaderi;
    location = locationi;
}

EngGLAttribute::EngGLAttribute(EngGLShader* shaderi, std::string str)
{
    shader = shaderi;
    setLocation(str);
}

bool EngGLAttribute::setLocation(std::string str) {
  location = gl::glGetAttribLocation(shader->getProgramID(), str.c_str());
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Nonexistent location of vertex attribute");
    return 1;
  }
  dlog("bind(std::string) OK");
  return 0;
}

void EngGLAttribute::setLocation(GLint locationi) { location = locationi; }

void EngGLAttribute::setShader(EngGLShader* shaderin) { shader = shaderin; }

bool EngGLAttribute::write(const GLfloat *data, unsigned length) {
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Attribute is unbinded");
    return 1;
  }
  shader->bind_program();
  if (length == 1)
    gl::glVertexAttrib1fv(location, data);
  else if (length == 2)
    gl::glVertexAttrib2fv(location, data);
  else if (length == 3)
    gl::glVertexAttrib3fv(location, data);
  else if (length == 4)
    gl::glVertexAttrib4fv(location, data);
  else {
    dlog("Add errlog");
    errlog.writeLog("Wrong length parameter");
    return 1;
  }
  dlog("write(const GLfloat*,unsigned) OK");
  return 0;
}

bool EngGLAttribute::write(const GLdouble *data, unsigned length) {
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Attribute is unbinded");
    return 1;
  }
  shader->bind_program();
  if (length == 1)
    gl::glVertexAttrib1dv(location, data);
  else if (length == 2)
    gl::glVertexAttrib2dv(location, data);
  else if (length == 3)
    gl::glVertexAttrib3dv(location, data);
  else if (length == 4)
    gl::glVertexAttrib4dv(location, data);
  else {
    dlog("Add errlog");
    errlog.writeLog("Wrong length parameter");
    return 1;
  }
  dlog("write(const GLdouble*,unsigned) OK");
  return 0;
}

bool EngGLAttribute::write(const GLshort *data, unsigned length) {
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Attribute is unbinded");
    return 1;
  }
  shader->bind_program();
  if (length == 1)
    gl::glVertexAttrib1sv(location, data);
  else if (length == 2)
    gl::glVertexAttrib2sv(location, data);
  else if (length == 3)
    gl::glVertexAttrib3sv(location, data);
  else if (length == 4)
    gl::glVertexAttrib4sv(location, data);
  else {
    dlog("Add errlog");
    errlog.writeLog("Wrong length parameter");
    return 1;
  }
  dlog("write(const GLshort*,unsigned) OK");
  return 0;
}

std::vector<std::string> EngGLAttribute::getLog() { return log.getLog(); }

std::vector<std::string> EngGLAttribute::getErrLog() { return errlog.getLog(); }

bool EngGLUniform::setLocation(std::string str) {
  location = gl::glGetUniformLocation(shader->getProgramID(), str.c_str());
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Nonexistent location of uniform");
    return 1;
  }
  dlog("bind(std::string) OK");
  return 0;
}

EngGLUniform::EngGLUniform(EngGLShader* shaderi, GLint locationi)
{
    shader = shaderi;
    location = locationi;
}

EngGLUniform::EngGLUniform(EngGLShader* shaderi, std::string str)
{
    shader = shaderi;
    setLocation(str);
}

void EngGLUniform::setLocation(GLint locationi) { location = locationi; }

void EngGLUniform::setShader(EngGLShader* shaderin) { shader = shaderin; }

bool EngGLUniform::write(const GLfloat *data, unsigned length, GLsizei count) {
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Attribute is unbinded");
    return 1;
  }
  shader->bind_program();
  if (length == 1)
    gl::glUniform1fv(location, count, data);
  else if (length == 2)
    gl::glUniform2fv(location, count, data);
  else if (length == 3)
    gl::glUniform3fv(location, count, data);
  else if (length == 4)
    gl::glUniform4fv(location, count, data);
  else {
    dlog("Add errlog");
    errlog.writeLog("Wrong length parameter");
    return 1;
  }
  dlog("write(const GLfloat*,unsigned,GLsizei) OK");
  return 0;
}

bool EngGLUniform::write(const GLint *data, unsigned length, GLsizei count) {
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Attribute is unbinded");
    return 1;
  }
  shader->bind_program();
  if (length == 1)
    gl::glUniform1iv(location, count, data);
  else if (length == 2)
    gl::glUniform2iv(location, count, data);
  else if (length == 3)
    gl::glUniform3iv(location, count, data);
  else if (length == 4)
    gl::glUniform4iv(location, count, data);
  else {
    dlog("Add errlog");
    errlog.writeLog("Wrong length parameter");
    return 1;
  }
  dlog("write(const GLint*,unsigned,GLsizei) OK");
  return 0;
}

bool EngGLUniform::write(const GLuint *data, unsigned length, GLsizei count) {
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Attribute is unbinded");
    return 1;
  }
  shader->bind_program();
  if (length == 1)
    gl::glUniform1uiv(location, count, data);
  else if (length == 2)
    gl::glUniform2uiv(location, count, data);
  else if (length == 3)
    gl::glUniform3uiv(location, count, data);
  else if (length == 4)
    gl::glUniform4uiv(location, count, data);
  else {
    dlog("Add errlog");
    errlog.writeLog("Wrong length parameter");
    return 1;
  }
  dlog("write(const GLuint*,unsigned,GLsizei) OK");
  return 0;
}

bool EngGLUniform::write(const GLfloat *data, unsigned rows, unsigned colums,
                         GLsizei count, gl::GLboolean transpose) {
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Attribute is unbinded");
    return 1;
  }
  shader->bind_program();
  if ((rows == 2) && (colums == 2))
    gl::glUniformMatrix2fv(location, count, transpose, data);
  else if ((rows == 3) && (colums == 3))
    gl::glUniformMatrix3fv(location, count, transpose, data);
  else if ((rows == 4) && (colums == 4))
    gl::glUniformMatrix4fv(location, count, transpose, data);
  else if ((rows == 2) && (colums == 3))
    gl::glUniformMatrix2x3fv(location, count, transpose, data);
  else if ((rows == 3) && (colums == 2))
    gl::glUniformMatrix3x2fv(location, count, transpose, data);
  else if ((rows == 2) && (colums == 4))
    gl::glUniformMatrix2x4fv(location, count, transpose, data);
  else if ((rows == 4) && (colums == 2))
    gl::glUniformMatrix4x2fv(location, count, transpose, data);
  else if ((rows == 3) && (colums == 4))
    gl::glUniformMatrix3x4fv(location, count, transpose, data);
  else if ((rows == 4) && (colums == 3))
    gl::glUniformMatrix4x3fv(location, count, transpose, data);
  else {
    dlog("Add errlog");
    errlog.writeLog("Wrong rows/colums parameter");
    return 1;
  }
#ifdef _DEBUG
  log.writeLog(std::string(
      "write(const GLfloat*,unsigned,unsigned,GLsizei,GLboolean) OK"));
#endif
  return 0;
}

bool EngGLUniform::write(const GLdouble *data, unsigned rows, unsigned colums,
                         GLsizei count, gl::GLboolean transpose) {
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Attribute is unbinded");
    return 1;
  }
  shader->bind_program();
  if ((rows == 2) && (colums == 2))
    gl::glUniformMatrix2dv(location, count, transpose, data);
  else if ((rows == 3) && (colums == 3))
    gl::glUniformMatrix3dv(location, count, transpose, data);
  else if ((rows == 4) && (colums == 4))
    gl::glUniformMatrix4dv(location, count, transpose, data);
  else if ((rows == 2) && (colums == 3))
    gl::glUniformMatrix2x3dv(location, count, transpose, data);
  else if ((rows == 3) && (colums == 2))
    gl::glUniformMatrix3x2dv(location, count, transpose, data);
  else if ((rows == 2) && (colums == 4))
    gl::glUniformMatrix2x4dv(location, count, transpose, data);
  else if ((rows == 4) && (colums == 2))
    gl::glUniformMatrix4x2dv(location, count, transpose, data);
  else if ((rows == 3) && (colums == 4))
    gl::glUniformMatrix3x4dv(location, count, transpose, data);
  else if ((rows == 4) && (colums == 3))
    gl::glUniformMatrix4x3dv(location, count, transpose, data);
  else {
    dlog("Add errlog");
    errlog.writeLog("Wrong rows/colums parameter");
    return 1;
  }
  dlog("write(const GLfloat*,unsigned,unsigned,GLsizei,GLboolean) OK");
  return 0;
}

std::vector<std::string> EngGLUniform::getLog() { return log.getLog(); }

std::vector<std::string> EngGLUniform::getErrLog() { return errlog.getLog(); }
