#ifndef ENGGLTEXTUREALLOCATOR_HPP
#define ENGGLTEXTUREALLOCATOR_HPP
#include <engInit.hpp>
//TODO: Add texture buffer
//TODO: Add compressed child class
//TODO: For release class delete all error queries
class EngGLTexture
{
public:
    EngGLTexture(unsigned,GLuint,gl::GLenum,gl::GLenum,GLuint, GLuint , GLuint);
    EngGLTexture (const EngGLTexture &) = delete;
    EngGLTexture& operator= (const EngGLTexture &) = delete;
    unsigned getID();
    gl::GLenum write(GLint offsetx, GLsizei sizex,
                     gl::GLenum formata, gl::GLenum typea, const void* data, GLuint level = 0);
    gl::GLenum write(GLint offsetx, GLsizei sizex,GLint offsety, GLsizei sizey,
                     gl::GLenum formata, gl::GLenum typea, const void* data, GLuint level = 0);
    gl::GLenum write(GLint offsetx, GLsizei sizex,GLint offsety, GLsizei sizey,GLint offsetz, GLsizei sizez,
                     gl::GLenum formata, gl::GLenum typea, const void* data, GLuint level = 0);
    gl::GLenum read(GLint offsetx, GLsizei sizex,GLint offsety, GLsizei sizey,GLint offsetz, GLsizei sizez,
                    gl::GLenum formata, gl::GLenum typea,GLsizei buffSize, void* data, GLuint level = 0);
    //gl::GLenum copy(); //TODO: ARB_copy_image
    //TODO: Add copy to buffer
    //TODO: ARB_clear_texture
    gl::GLenum parametr(gl::GLenum pname, GLfloat param);
    gl::GLenum parametr(gl::GLenum pname, GLint param);
    gl::GLenum parametr(gl::GLenum pname, const GLfloat* param);
    gl::GLenum parametr(gl::GLenum pname, const GLint* param);
    gl::GLenum parametrI(gl::GLenum pname, const GLint* param);
    gl::GLenum parametrI(gl::GLenum pname, const GLuint* param);
private:
    unsigned id;
    GLuint texture;
    gl::GLenum target;
    gl::GLenum iformat;
    GLuint size[3];
};

class EngGLTextureAllocator
{
public:
    static EngGLTexture* allocateUncompressed(gl::GLenum target, gl::GLenum format,
                                                    GLsizei size, GLsizei levels, gl::GLenum &err);
    static EngGLTexture* allocateUncompressed(gl::GLenum target, gl::GLenum format, GLsizei sizex,
                                                    GLsizei sizey, GLsizei levels, gl::GLenum &err);
    static EngGLTexture* allocateUncompressed(gl::GLenum target, gl::GLenum format, GLsizei sizex,
                                                    GLsizei sizey, GLsizei sizez, GLsizei levels, gl::GLenum &err);
    static void release(EngGLTexture* &id, gl::GLenum &err);
    static void clearAll();
    static std::vector<std::string> getLog();
    static std::vector<std::string> getErrLog();
private:
    static std::vector<GLuint> textures;
    //static std::vector<EngGLTexture*> textures;
    static std::queue<unsigned> to_delete;
    static Log log;
    static Log errlog;
    //static GLsizeiptr cursize;
    //static GLsizeiptr maxsize;
};

#endif // ENGGLTEXTUREALLOCATOR_HPP
