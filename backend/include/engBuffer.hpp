#ifndef ENGBUFFER_HPP
#define ENGBUFFER_HPP
#include <engInit.hpp>
#include <engShader.hpp>
#include <initializer_list>

class EngGLbuffer {
public:
  EngGLbuffer();
  void allocate(GLsizei size, gl::GLenum type, GLvoid *data = NULL);
  void bind();
  void bindBase(GLuint);
  void write(GLvoid *, GLsizei, GLsizei offset = 0);
  void *get_ptr(gl::GLenum param = gl::GLenum(GL_WRITE_ONLY));
  void *get_ptr(GLsizei, GLsizei, gl::BufferAccessMask param = gl::BufferAccessMask(GL_MAP_WRITE_BIT));
  void clear_ptr();
  void clear();
  ~EngGLbuffer();

protected:
  void setTarget(gl::GLenum);
  void setControll(GLuint *);

private:
  GLuint buffObj;
  GLuint *binded_buff;
  gl::GLenum target;
};

class EngGLVBO : public EngGLbuffer {
public:
  EngGLVBO();
  EngGLVBO(EngGLShader*, GLint locationi = -1);
  EngGLVBO(EngGLShader*, std::string);
  void setShader(EngGLShader*);
  bool setLocation(std::string);
  bool setLocation(GLint);
  void bind(GLint vecsize = 4, gl::GLenum type = gl::GLenum(GL_FLOAT),
            gl::GLboolean normalized = gl::GLboolean(GL_FALSE), GLsizei stride = 0,
            GLvoid *ptr = NULL);
  void enable();
  void disable();
  void render(GLsizei, GLsizei offset = 0, gl::GLenum type = gl::GLenum(GL_TRIANGLES));
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
private:
  GLint location;
  EngGLShader* shader;
  static GLuint binded_vbo;
  Log log;
  Log errlog;
};

enum EngGLInfoType
{
    ENG_INDEX,
    ENG_OFFSET,
    ENG_MSTRIDE,
    ENG_ASTRIDE
};

class EngGLUBO : public EngGLbuffer {
public:
  EngGLUBO();
  EngGLUBO(EngGLShader*, GLint locationi = -1);
  EngGLUBO(EngGLShader*, std::string);
  void setShader(EngGLShader*);
  void setLocation(GLint locationi = -1);
  bool setLocation(std::string);
  unsigned int load(gl::GLenum type);
  template <typename T>
  void writeUBOScalar (T,unsigned);
  template <typename T>
  void writeUBOVec (T*,unsigned,unsigned);
  template <typename T>
  void writeUBOArr (T*,unsigned,unsigned);
  template <typename T>
  void writeUBOMat (T*,unsigned,unsigned,unsigned);
  template <typename T>
  void writeUBOVecArr (std::initializer_list<T*>,unsigned,unsigned);
  template <typename T>
  void writeUBOMatArr (std::initializer_list<T*>,unsigned,unsigned,unsigned);
  void enable (GLuint, bool must_bind = false);
  GLuint getVarInfo (unsigned, EngGLInfoType);
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
  void disable ();
  void clear();
private:
  GLint location;
  GLuint bpoint;
  EngGLShader* shader;
  static GLuint binded_ubo;
  GLint buff_size;
  std::vector<GLuint> indexes;
  std::vector<GLint> offsets;
  std::vector<GLint> mstrides;
  std::vector<GLint> astrides;
  Log log;
  Log errlog;
};

//TODO: implement atomic counters

#include <EngGLUBOTemplate.hpp>

#endif // ENGBUFFER_HPP
