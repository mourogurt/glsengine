#ifndef ENGBUFFER_HPP
#define ENGBUFFER_HPP
#include <engInit.hpp>
#include <engShader.hpp>
#include <initializer_list>

class EngGLbuffer {
public:
  EngGLbuffer();
  void allocate(GLsizei size, GLenum type, GLvoid *data = NULL);
  void bind();
  void bindBase(GLuint);
  void write(GLvoid *, GLsizei, GLsizei offset = 0);
  void *get_ptr(GLenum param = GL_WRITE_ONLY);
  void *get_ptr(GLsizei, GLsizei, GLenum param = GL_WRITE_ONLY);
  void clear_ptr();
  void clear();
  ~EngGLbuffer();

protected:
  void setTarget(GLenum);
  void setControll(GLuint *);

private:
  GLuint buffObj;
  GLuint *binded_buff;
  GLenum target;
};

class EngGLVBO : public EngGLbuffer {
public:
  EngGLVBO();
  EngGLVBO(EngGLShader*, GLint locationi = -1);
  EngGLVBO(EngGLShader*, std::string);
  void setShader(EngGLShader*);
  bool setLocation(std::string);
  bool setLocation(GLint);
  void bind(GLint vecsize = 4, GLenum type = GL_FLOAT,
            GLboolean normalized = GL_FALSE, GLsizei stride = 0,
            GLvoid *ptr = NULL);
  void enable();
  void disable();
  void render(GLsizei, GLsizei offset = 0, GLenum type = GL_TRIANGLES);
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
private:
  GLint location;
  EngGLShader* shader;
  static GLuint binded_vbo;
  Log log;
  Log errlog;
};

class EngGLUBO : public EngGLbuffer {
public:
  EngGLUBO();
  EngGLUBO(EngGLShader*, GLint locationi = -1);
  EngGLUBO(EngGLShader*, std::string);
  void setShader(EngGLShader*);
  void setLocation(GLint locationi = -1);
  bool setLocation(std::string);
  unsigned int load(GLenum type);
  template <typename T>
  void writeUBOScalar (unsigned,T);
  template <typename T>
  void writeUBOVec (unsigned,unsigned,T*);
  template <typename T>
  void writeUBOArr (unsigned,unsigned,T*);
  template <typename T>
  void writeUBOMat (unsigned,unsigned,unsigned,T*);
  template <typename T>
  void writeUBOVecArr (unsigned,unsigned,std::initializer_list<T*>);
  template <typename T>
  void writeUBOMatArr (unsigned,unsigned,unsigned,std::initializer_list<T*>);
  void enable (GLuint, bool must_bind = false);
  void disable ();
  void clear();
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
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

#include <EngGLUBOTemplate.hpp>

#endif // ENGBUFFER_HPP
