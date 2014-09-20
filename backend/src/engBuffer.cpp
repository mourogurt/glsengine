#include "engBuffer.hpp"

GLuint EngGLVBO::binded_vbo = 0;
GLuint EngGLUBO::binded_ubo = 0;

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

void EngGLbuffer::bindBase(GLuint bind_point) {
   glBindBufferBase(target, bind_point, buffObj);
}

void EngGLbuffer::write(GLvoid *data, GLsizei size, GLsizei offset) {
  bind();
  glBufferSubData(target, offset, size, data);
}

void *EngGLbuffer::get_ptr(GLenum param) {
  if (*binded_buff != buffObj)
    clear_ptr();
  bind();
  void *ptr = glMapBuffer(target, param);
  return ptr;
}

void *EngGLbuffer::get_ptr(GLsizei offset, GLsizei size, GLenum param) {
  if (*binded_buff != buffObj)
    clear_ptr();
  bind();
  void *ptr = glMapBufferRange(target, offset, size, param);
  return ptr;
}

void EngGLbuffer::clear_ptr()
{
    glUnmapBuffer(target);
}

void EngGLbuffer::clear() {
  if (*binded_buff != buffObj)
    clear_ptr();
  bind();
  glBufferData(target, 0, NULL, GL_STATIC_DRAW);
}

EngGLbuffer::~EngGLbuffer() {
  clear();
  glDeleteBuffers(1, &buffObj);
}

EngGLVBO::EngGLVBO() {
  setTarget(GL_ARRAY_BUFFER);
  setControll(&binded_vbo);
}

EngGLVBO::EngGLVBO(EngGLShader* shaderi, GLint locationi)
{
    setTarget(GL_ARRAY_BUFFER);
    setControll(&binded_vbo);
    shader = shaderi;
    location = locationi;
}

EngGLVBO::EngGLVBO(EngGLShader* shaderi, std::string str)
{
    setTarget(GL_ARRAY_BUFFER);
    setControll(&binded_vbo);
    shader = shaderi;
    setLocation(str);
}

void EngGLVBO::setShader(EngGLShader* shaderin) { shader = shaderin; }

bool EngGLVBO::setLocation(std::string str) {
  location = glGetAttribLocation(shader->getProgramID(), str.c_str());
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Nonexistent location of vertex attribute");
    return 1;
  }
  dlog("setLocation(std::string,GLuint) OK");
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

EngGLUBO::EngGLUBO()
{
    setTarget(GL_UNIFORM_BUFFER);
    setControll(&binded_ubo);
}

EngGLUBO::EngGLUBO(EngGLShader* shaderi, GLint locationi)
{
    setTarget(GL_UNIFORM_BUFFER);
    setControll(&binded_ubo);
    shader = shaderi;
    location = locationi;
}

EngGLUBO::EngGLUBO(EngGLShader* shaderi, std::string str)
{
    setTarget(GL_UNIFORM_BUFFER);
    setControll(&binded_ubo);
    shader = shaderi;
    setLocation(str);
}

void EngGLUBO::setShader(EngGLShader* shaderi)
{
    shader = shaderi;
}

void EngGLUBO::setLocation(GLint locationi)
{
    location = locationi;
}

bool EngGLUBO::setLocation(std::string name)
{
    location = glGetUniformBlockIndex(shader->getProgramID(),name.c_str());
    if (location == -1) {
      dlog("Add errlog");
      errlog.writeLog("Nonexistent location of uniform buffer object");
      return 1;
    }
    dlog("setLocation(std::string,GLuint) OK");
    return 0;
}

unsigned int EngGLUBO::load(GLenum type)
{
    clear();
    GLint unifLen = 0;
    glGetActiveUniformBlockiv(shader->getProgramID(), location, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &unifLen);
    if (unifLen == 0)
    {
        dlog("Add errlog");
        errlog.writeLog("Nonexistent location of uniform buffer object");
        clear();
        return 0;
    }
    indexes.resize(unifLen);
    offsets.resize(unifLen);
    mstrides.resize(unifLen);
    astrides.resize(unifLen);
    glGetActiveUniformBlockiv(shader->getProgramID(), location, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)&indexes[0]);
    glGetActiveUniformsiv(shader->getProgramID(),unifLen,&indexes[0],GL_UNIFORM_OFFSET,&offsets[0]);
    glGetActiveUniformsiv(shader->getProgramID(),unifLen,&indexes[0],GL_UNIFORM_MATRIX_STRIDE,&mstrides[0]);
    glGetActiveUniformsiv(shader->getProgramID(),unifLen,&indexes[0],GL_UNIFORM_ARRAY_STRIDE,&astrides[0]);
    glGetActiveUniformBlockiv(shader->getProgramID(), location,GL_UNIFORM_BLOCK_DATA_SIZE, &buff_size);
    allocate(buff_size,type);
    dlog("load(GLenum) OK");
    return unifLen;
}

void EngGLUBO::enable(GLuint bind_point, bool must_bind)
{
    if (must_bind)
        glUniformBlockBinding(shader->getProgramID(), location, bind_point);
    bindBase(bind_point);
    bpoint = bind_point;
}

void EngGLUBO::disable()
{
    glBindBufferBase(GL_UNIFORM_BUFFER,bpoint,0);
}

void EngGLUBO::clear()
{
    indexes.clear();
    offsets.clear();
    mstrides.clear();
    astrides.clear();
    EngGLbuffer::clear();
}

std::vector<std::string> EngGLUBO::getLog() { return log.getLog(); }

std::vector<std::string> EngGLUBO::getErrLog() { return errlog.getLog(); }
