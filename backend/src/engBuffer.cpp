#include "engBuffer.hpp"

GLuint EngGLVBO::binded_vbo = 0;
GLuint EngGLUBO::binded_ubo = 0;

EngGLbuffer::EngGLbuffer() {
  buffObj = 0;
  maped = GL_FALSE;
  target = gl::GLenum(0);
  gl::glGenBuffers(1, &buffObj);
}

void EngGLbuffer::setTarget(gl::GLenum targeti) { target = targeti; }

void EngGLbuffer::setControll(GLuint *controll_buf) {
  binded_buff = controll_buf;
}

void EngGLbuffer::allocate(GLsizei size, gl::GLenum type, GLvoid *data) {
  bind();
  gl::glBufferData(target, size, data, type);
}

void EngGLbuffer::bind() {
  if (*binded_buff != buffObj) {
    gl::glBindBuffer(target, buffObj);
    *binded_buff = buffObj;
  }
}

void EngGLbuffer::bindBase(GLuint bind_point) {
   gl::glBindBufferBase(target, bind_point, buffObj);
}

void EngGLbuffer::write(GLvoid *data, GLsizei size, GLsizei offset) {
  bind();
  gl::glBufferSubData(target, offset, size, data);
}

void *EngGLbuffer::get_ptr(gl::GLenum param) {
  if (*binded_buff != buffObj)
    clear_ptr();
  bind();
  void *ptr = gl::glMapBuffer(target, param);
  if (ptr != NULL) maped = GL_TRUE;
  return ptr;
}

void *EngGLbuffer::get_ptr(GLsizei offset, GLsizei size, gl::BufferAccessMask param) {
  if (*binded_buff != buffObj)
    clear_ptr();
  bind();
  void *ptr = gl::glMapBufferRange(target, offset, size, param);
  if (ptr != NULL) maped = GL_TRUE;
  return ptr;
}

void EngGLbuffer::clear_ptr()
{
    if (maped == GL_TRUE)
    {
        gl::glUnmapBuffer(target);
        maped = GL_FALSE;
    }
}

void EngGLbuffer::clear() {
  if (*binded_buff == buffObj)
    clear_ptr();
  bind();
  gl::glBufferData(target, 0, NULL, gl::GLenum(GL_STATIC_DRAW));
}

EngGLbuffer::~EngGLbuffer() {
  clear();
  gl::glDeleteBuffers(1, &buffObj);
}

EngGLVBO::EngGLVBO() {
  setTarget(gl::GLenum(GL_ARRAY_BUFFER));
  setControll(&binded_vbo);
}

EngGLVBO::EngGLVBO(EngGLShader* shaderi, GLint locationi)
{
    setTarget(gl::GLenum(GL_ARRAY_BUFFER));
    setControll(&binded_vbo);
    shader = shaderi;
    location = locationi;
}

EngGLVBO::EngGLVBO(EngGLShader* shaderi, std::string str)
{
    setTarget(gl::GLenum(GL_ARRAY_BUFFER));
    setControll(&binded_vbo);
    shader = shaderi;
    setLocation(str);
}

void EngGLVBO::setShader(EngGLShader* shaderin) { shader = shaderin; }

bool EngGLVBO::setLocation(std::string str) {
  location = gl::glGetAttribLocation(shader->getProgramID(), str.c_str());
  if (location == -1) {
    dlog("Add errlog");
    errlog.writeLog("Nonexistent location of vertex attribute");
    return 1;
  }
  dlog("setLocation(std::string,GLuint) OK");
  return 0;
}

void EngGLVBO::bind(GLint vecsize, gl::GLenum type, gl::GLboolean normalized,
                  GLsizei stride, GLvoid *ptr) {
  EngGLbuffer::bind();
  gl::glVertexAttribPointer(location, vecsize, type, normalized, stride, ptr);
}

void EngGLVBO::enable() {
  EngGLbuffer::bind();
  gl::glEnableVertexAttribArray(location);
}

void EngGLVBO::disable() {
  EngGLbuffer::bind();
  gl::glDisableVertexAttribArray(location);
}

void EngGLVBO::render(GLsizei size, GLsizei offset, gl::GLenum type) {
  EngGLbuffer::bind();
  gl::glDrawArrays(type, offset, size);
}

std::vector<std::string> EngGLVBO::getLog() { return log.getLog(); }

std::vector<std::string> EngGLVBO::getErrLog() { return errlog.getLog(); }

EngGLUBO::EngGLUBO()
{
    setTarget(gl::GLenum(GL_UNIFORM_BUFFER));
    setControll(&binded_ubo);
}

EngGLUBO::EngGLUBO(EngGLShader* shaderi, GLint locationi)
{
    setTarget(gl::GLenum(GL_UNIFORM_BUFFER));
    setControll(&binded_ubo);
    shader = shaderi;
    location = locationi;
}

EngGLUBO::EngGLUBO(EngGLShader* shaderi, std::string str)
{
    setTarget(gl::GLenum(GL_UNIFORM_BUFFER));
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
    location = gl::glGetUniformBlockIndex(shader->getProgramID(),name.c_str());
    if (location == -1) {
      dlog("Add errlog");
      errlog.writeLog("Nonexistent location of uniform buffer object");
      return 1;
    }
    dlog("setLocation(std::string,GLuint) OK");
    return 0;
}

unsigned int EngGLUBO::load(gl::GLenum type)
{
    clear();
    GLint unifLen = 0;
    gl::glGetActiveUniformBlockiv(shader->getProgramID(), location, gl::GLenum(GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS), &unifLen);
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
    gl::glGetActiveUniformBlockiv(shader->getProgramID(), location, gl::GLenum(GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES), (GLint*)&indexes[0]);
    gl::glGetActiveUniformsiv(shader->getProgramID(),unifLen,&indexes[0],gl::GLenum(GL_UNIFORM_OFFSET),&offsets[0]);
    gl::glGetActiveUniformsiv(shader->getProgramID(),unifLen,&indexes[0],gl::GLenum(GL_UNIFORM_MATRIX_STRIDE),&mstrides[0]);
    gl::glGetActiveUniformsiv(shader->getProgramID(),unifLen,&indexes[0],gl::GLenum(GL_UNIFORM_ARRAY_STRIDE),&astrides[0]);
    gl::glGetActiveUniformBlockiv(shader->getProgramID(), location,gl::GLenum(GL_UNIFORM_BLOCK_DATA_SIZE), &buff_size);
    allocate(buff_size,type);
    dlog("load(GLenum) OK");
    return unifLen;
}

void EngGLUBO::enable(GLuint bind_point, bool must_bind)
{
    if (must_bind)
        gl::glUniformBlockBinding(shader->getProgramID(), location, bind_point);
    bindBase(bind_point);
    bpoint = bind_point;
}

GLuint EngGLUBO::getVarInfo(unsigned index, EngGLInfoType type)
{
    GLuint result = 0;
    switch (type) {
    case ENG_INDEX:
        result = indexes[index];
        break;
    case ENG_OFFSET:
        result = offsets[index];
        break;
    case ENG_ASTRIDE:
        result = astrides[index];
        break;
    case ENG_MSTRIDE:
        result = mstrides[index];
        break;
    default:
        dlog("Add errlog");
        errlog.writeLog("Invalid type");
        return 0;
        break;
    }
    dlog("getVarInfo(unsigned,EngGLInfoType) OK");
    return result;
}

std::vector<std::string> EngGLUBO::getLog() { return log.getLog(); }

std::vector<std::string> EngGLUBO::getErrLog() { return errlog.getLog(); }

void EngGLUBO::disable()
{
    gl::glBindBufferBase(gl::GLenum(GL_UNIFORM_BUFFER),bpoint,0);
}

void EngGLUBO::clear()
{
    indexes.clear();
    offsets.clear();
    mstrides.clear();
    astrides.clear();
    EngGLbuffer::clear();
}
