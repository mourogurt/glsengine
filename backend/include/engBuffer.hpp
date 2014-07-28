#ifndef ENGBUFFER_HPP
#define ENGBUFFER_HPP
#include "engInit.hpp"
#include "engShader.hpp"

class EngGLbuffer {
public:
  EngGLbuffer();
  void allocate(GLsizei size, GLenum type, GLvoid *data = NULL);
  void bind();
  void write(GLvoid *, GLsizei, GLsizei offset = 0);
  void *get_ptr(GLenum param = GL_WRITE_ONLY);
  void *get_ptr(GLsizei, GLsizei, GLenum param = GL_WRITE_ONLY);
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
  void setShader(EngShader*);
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
  EngShader* shader;
  static GLuint binded_vab;
  Log log;
  Log errlog;
};

/*class EngUBO : public EngGLbuffer {
public:
  EngUBO();
  bool setLocation(std::string, GLuint);
  bool setLocation(GLint);
  void bind(bool);

};*/

#endif // ENGBUFFER_HPP
