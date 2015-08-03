#include "engGLTextureAllocator.hpp"

std::vector<GLuint> EngGLTextureAllocator::textures;
//static std::vector<EngGLTexture*> textures;
std::queue<unsigned> EngGLTextureAllocator::to_delete;
Log EngGLTextureAllocator::log;
Log EngGLTextureAllocator::errlog;
//GLsizeiptr EngGLTextureAllocator::cursize;
//GLsizeiptr EngGLTextureAllocator::maxsize;

EngGLTexture::EngGLTexture(unsigned ida,GLuint texturea,gl::GLenum targeta,gl::GLenum formata,GLuint sizexa, GLuint sizeya , GLuint sizeza)
{
    id = ida;
    texture = texturea;
    target = targeta;
    iformat = formata;
    size[0] = sizexa;
    size[1] = sizeya;
    size[2] = sizeza;
}

unsigned EngGLTexture::getID()
{
    return id;
}

gl::GLenum EngGLTexture::write(GLint offsetx, GLsizei sizex,
                               gl::GLenum formata, gl::GLenum typea, const void* data, GLuint level)
{
    gl::glTextureSubImage1D(texture,level,offsetx,sizex,formata,typea,data);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::write(GLint offsetx, GLsizei sizex,GLint offsety, GLsizei sizey,
                               gl::GLenum formata, gl::GLenum typea, const void* data, GLuint level)
{
    gl::glTextureSubImage2D(texture,level,offsetx,offsety,sizex,sizey,formata,typea,data);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::write(GLint offsetx, GLsizei sizex,GLint offsety, GLsizei sizey,GLint offsetz, GLsizei sizez,
                               gl::GLenum formata, gl::GLenum typea, const void* data, GLuint level)
{
    gl::glTextureSubImage3D(texture,level,offsetx,offsety,offsetz,sizex,sizey,sizez,formata,typea,data);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::read(GLint offsetx, GLsizei sizex,GLint offsety, GLsizei sizey,GLint offsetz, GLsizei sizez,
                              gl::GLenum formata, gl::GLenum typea,GLsizei buffSize, void* data, GLuint level)
{
    gl::glGetTextureSubImage(texture,level,offsetx,offsety,offsetz,sizex,sizey,sizez,formata,typea,buffSize,data);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::parametr(gl::GLenum pname, GLfloat param)
{
    gl::glTextureParameterf(texture,pname,param);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::parametr(gl::GLenum pname, GLint param)
{
    gl::glTextureParameteri(texture,pname,param);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::parametr(gl::GLenum pname, const GLfloat* param)
{
    gl::glTextureParameterfv(texture,pname,param);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::parametr(gl::GLenum pname, const GLint* param)
{
    gl::glTextureParameteriv(texture,pname,param);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::parametrI(gl::GLenum pname, const GLint* param)
{
    gl::glTextureParameterIiv(texture,pname,param);
    return gl::glGetError();
}

gl::GLenum EngGLTexture::parametrI(gl::GLenum pname, const GLuint* param)
{
    gl::glTextureParameterIuiv(texture,pname,param);
    return gl::glGetError();
}

EngGLTexture* EngGLTextureAllocator::allocateUncompressed(gl::GLenum target, gl::GLenum format, GLsizei size, GLsizei levels, gl::GLenum &err)
{
    //TODO: Query limits
    GLuint texture;
    gl::glCreateTextures(target,1,&texture);
    gl::glTextureStorage1D(texture,levels,format,size);
    err = gl::glGetError();
    if (err != gl::GLenum(GL_NO_ERROR))
    {
        dlog("Add errlog");
        errlog.writeLog(std::string("Texture creating failed with error:" +
                                    std::to_string(static_cast<int>(err))));
        return NULL;
    }
    EngGLTexture* tmp = new EngGLTexture(textures.size(),texture,target,format,size,0,0);
    if (to_delete.size() == 0)
    {
        textures.push_back(texture);
    } else
    {
        unsigned id = to_delete.front();
        to_delete.pop();
        textures[id] = texture;
    }
    return tmp;
}

EngGLTexture* EngGLTextureAllocator::allocateUncompressed(gl::GLenum target, gl::GLenum format, GLsizei sizex, GLsizei sizey, GLsizei levels, gl::GLenum &err)
{
    //TODO: Query limits
    GLuint texture;
    gl::glCreateTextures(target,1,&texture);
    gl::glTextureStorage2D(texture,levels,format,sizex,sizey);
    err = gl::glGetError();
    if (err != gl::GLenum(GL_NO_ERROR))
    {
        dlog("Add errlog");
        errlog.writeLog(std::string("Texture creating failed with error:" +
                                    std::to_string(static_cast<int>(err))));
        return NULL;
    }
    EngGLTexture* tmp = new EngGLTexture(textures.size(),texture,target,format,sizex,sizey,0);
    if (to_delete.size() == 0)
    {
        textures.push_back(texture);
    } else
    {
        unsigned id = to_delete.front();
        to_delete.pop();
        textures[id] = texture;
    }
    return tmp;
}

EngGLTexture* EngGLTextureAllocator::allocateUncompressed(gl::GLenum target, gl::GLenum format, GLsizei sizex, GLsizei sizey, GLsizei sizez, GLsizei levels, gl::GLenum &err)
{
    //TODO: Query limits
    GLuint texture;
    gl::glCreateTextures(target,1,&texture);
    gl::glTextureStorage3D(texture,levels,format,sizex,sizey,sizez);
    err = gl::glGetError();
    if (err != gl::GLenum(GL_NO_ERROR))
    {
        dlog("Add errlog");
        errlog.writeLog(std::string("Texture creating failed with error:" +
                                    std::to_string(static_cast<int>(err))));
        return NULL;
    }
    EngGLTexture* tmp = new EngGLTexture(textures.size(),texture,target,format,sizex,sizey,sizez);
    if (to_delete.size() == 0)
    {
        textures.push_back(texture);
    } else
    {
        unsigned id = to_delete.front();
        to_delete.pop();
        textures[id] = texture;
    }
    return tmp;
}

void EngGLTextureAllocator::release(EngGLTexture* &id, gl::GLenum &err)
{
    gl::glDeleteTextures(1,&textures[id->getID()]);
    err = gl::glGetError();
    if (err != gl::GLenum(GL_NO_ERROR))
    {
        dlog("Add errlog");
        errlog.writeLog(std::string("Texture creating failed with error:" +
                                    std::to_string(static_cast<int>(err))));
        return;
    }
    to_delete.push(id->getID());
    delete id;
    id = NULL;
    return;
}

void EngGLTextureAllocator::clearAll()
{
    gl::glDeleteTextures(textures.size(),&textures[0]);
    textures.clear();
    to_delete = std::queue<unsigned>();
}

