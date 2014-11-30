#ifndef ENGTEXTURE_HPP
#define ENGTEXTURE_HPP
#include <engInit.hpp>
#include <engValue.hpp>

class EngGLTexture
{
public:
   EngGLTexture();
   void bind();
   ~EngGLTexture();
protected:
   void setTarget(gl::GLenum);
   void setControll(GLuint *);
private:
   GLuint texture;
   GLuint* binded_texture;
   gl::GLenum target;

};

class EngGLTexture2D : EngGLTexture
{
public:
    EngGLTexture2D();
    void allocate(GLsizei,GLsizei,GLint levels = 1,gl::GLenum ifmt = gl::GLenum(GL_RGBA8));
    void write(GLvoid*,GLsizei,GLsizei,GLint xoffset = 0,GLint yoffset = 0,GLint level = 0,
               gl::GLenum fmt = gl::GLenum(GL_BGRA),gl::GLenum type = gl::GLenum(GL_UNSIGNED_BYTE));
    void* get_image(GLint level = 0,gl::GLenum fmt = gl::GLenum(GL_BGRA),
                    gl::GLenum type = gl::GLenum(GL_UNSIGNED_BYTE)); //TODO: get subimage when will be implemented in mesa
    std::vector<std::string> getLog();
    std::vector<std::string> getErrLog();
    void clear(); //FIXME: add clear function(probably will think about texture architecture)
    //~EngGLTexture2D();
private:
    static GLuint binded_tex2d;
    GLsizei width;
    GLsizei height;
    Log log;
    Log errlog;
};

class EngGLSampler
{
public:
    EngGLSampler();
    EngGLSampler(const GLint&);
    void setUnit(const GLint&);
    void setUnit(EngGLUniform&,const GLint&); //TODO: without EngGLUniform?
    void property(gl::GLenum,GLint);
    void property(gl::GLenum,GLfloat);
    void setData (EngGLTexture*);
    void load();
    ~EngGLSampler();
private:
    GLint unit;
    GLuint sampler;
    EngGLTexture* texture;
};

#endif // ENGTEXTURE_HPP
