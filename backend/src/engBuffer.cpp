#include "engBuffer.hpp"

GLuint EngGLVBO::binded_vab = 0;

EngGLbuffer::EngGLbuffer() {
  buffObj = 0;
  target = 0;
  glGenBuffers(1, &buffObj);
}

void EngGLbuffer::setTarget(GLenum targeti) { target = targeti; }

void EngGLbuffer::setControll(GLuint *controll_buf) {
  binded_buff = controll_buf;
}

void EngGLbuffer::allocate(GLsizei size, GLenum type, GLvoid *data) {
  bind();
  glBufferData(target, size, data, type);
}

void EngGLbuffer::bind() {
  if (*binded_buff != buffObj) {
    glBindBuffer(target, buffObj);
    *binded_buff = buffObj;
  }
}

void EngGLbuffer::write(GLvoid *data, GLsizei size, GLsizei offset) {
  bind();
  glBufferSubData(target, offset, size, data);
}

void *EngGLbuffer::get_ptr(GLenum param) {
  bind();
  if (*binded_buff != buffObj)
    glUnmapBuffer(target);
  void *ptr = glMapBuffer(target, param);
  return ptr;
}

void *EngGLbuffer::get_ptr(GLsizei offset, GLsizei size, GLenum param) {
  bind();
  if (*binded_buff != buffObj)
    glUnmapBuffer(target);
  void *ptr = glMapBufferRange(target, offset, size, param);
  return ptr;
}

void EngGLbuffer::clear() {
  if (*binded_buff != buffObj)
    glUnmapBuffer(target);
  bind();
  glBufferData(target, 0, NULL, GL_STATIC_DRAW);
}

EngGLbuffer::~EngGLbuffer() {
  clear();
  glDeleteBuffers(1, &buffObj);
}

EngGLVBO::EngGLVBO() {
  setTarget(GL_ARRAY_BUFFER);
  setControll(&binded_vab);
}

void EngGLVBO::setShader(EngShader* shaderin) { shader = shaderin; }

bool EngGLVBO::setLocation(std::string str) {
  location = glGetAttribLocation(shader->getProgramID(), str.c_str());
  if (location == -1) {
#ifdef _DEBUG
    log.writeLog(std::string("Add errlog"));
#endif
    errlog.writeLog("Nonexistent location of vertex attribute");
    return 1;
  }
#ifdef _DEBUG
  log.writeLog("setLocation(std::string,GLuint) OK");
#endif
  return 0;
}

void EngGLVBO::bind(GLint vecsize, GLenum type, GLboolean normalized,
                  GLsizei stride, GLvoid *ptr) {
  EngGLbuffer::bind();
  glVertexAttribPointer(location, vecsize, type, normalized, stride, ptr);
}

void EngGLVBO::enable() {
  EngGLbuffer::bind();
  glEnableVertexAttribArray(location);
}

void EngGLVBO::disable() {
  EngGLbuffer::bind();
  glDisableVertexAttribArray(location);
}

void EngGLVBO::render(GLsizei size, GLsizei offset, GLenum type) {
  EngGLbuffer::bind();
  glDrawArrays(type, offset, size);
}

std::vector<std::string> EngGLVBO::getLog() { return log.getLog(); }

std::vector<std::string> EngGLVBO::getErrLog() { return errlog.getLog(); }
