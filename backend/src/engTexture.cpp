#include "engTexture.hpp"

GLuint EngGLTexture2D::binded_tex2d = 0;

EngGLTexture::EngGLTexture()
{
  texture = 0;
  target = gl::GLenum(0);
  gl::glGenTextures(1, &texture);
}

void EngGLTexture::setTarget(gl::GLenum targeti) { target = targeti; }

void EngGLTexture::setControll(GLuint *controll_tex)
{
    binded_texture = controll_tex;
}

void EngGLTexture::bind()
{
    if (*binded_texture != texture) {
       gl::glBindTexture(target, texture);
       *binded_texture = texture;
    }
}

EngGLTexture::~EngGLTexture()
{
    gl::glDeleteTextures(1,&texture);
}

EngGLTexture2D::EngGLTexture2D()
{
    setTarget(gl::GLenum(GL_TEXTURE_2D));
    setControll(&binded_tex2d);
}

void EngGLTexture2D::allocate(GLsizei widthi, GLsizei heighti, GLint levels, gl::GLenum ifmt)
{
    bind();
    gl::glTexStorage2D(gl::GLenum(GL_TEXTURE_2D),levels,ifmt,widthi,heighti);//TODO: make border
                                                                          //TODO: add mipmaps
                                                                          //TODO: Probably need to implement this using glTexImage
    width = widthi;
    height = heighti;

}

void EngGLTexture2D::write(GLvoid *data, GLsizei width, GLsizei height, GLint xoffset, GLint yoffset, GLint level, gl::GLenum fmt, gl::GLenum type)
{
    bind();
    gl::glTexSubImage2D(gl::GLenum(GL_TEXTURE_2D),level,xoffset,yoffset,width,height,fmt,type,data); //TODO: some params save in class
}

void* EngGLTexture2D::get_image(GLint level, gl::GLenum fmt, gl::GLenum type)
{
    bind();
    unsigned nchannels;
    unsigned typesize;
    GLsizei levelwidth = std::max(1u,width/(level+1u));
    GLsizei levelheight = std::max(1u,height/(level+1u));
    switch (fmt)
    {
        case gl::GLenum(GL_RED) : nchannels = 1; break;
        case gl::GLenum(GL_GREEN) : nchannels = 1; break;
        case gl::GLenum(GL_BLUE) : nchannels = 1; break;
        case gl::GLenum(GL_RG) : nchannels = 2; break;
        case gl::GLenum(GL_RGB) : nchannels = 3; break;
        case gl::GLenum(GL_BGR) : nchannels = 3; break;
        case gl::GLenum(GL_BGRA) : nchannels = 4; break;
        case gl::GLenum(GL_RGBA) : nchannels = 4; break;
        default : dlog("Add errlog"); errlog.writeLog("Unknown or unimplimented format"); return NULL; break;
    }
    switch (type)
    {
        case gl::GLenum(GL_UNSIGNED_BYTE) : typesize = sizeof(unsigned char); break;
        case gl::GLenum(GL_BYTE) : typesize = sizeof(char); break;
        case gl::GLenum(GL_UNSIGNED_SHORT) : typesize = sizeof(unsigned short); break;
        case gl::GLenum(GL_SHORT) : typesize = sizeof(short); break;
        case gl::GLenum(GL_UNSIGNED_INT) : typesize = sizeof(unsigned int); break;
        case gl::GLenum(GL_INT) : typesize = sizeof(int); break;
        case gl::GLenum(GL_FLOAT) : typesize = sizeof(float); break;
        default : dlog("Add errlog"); errlog.writeLog("Unknown or unimplimented type"); return NULL; break;
    } //FIXME: very dirty hack, need to reimplement
    void* pixels = malloc(levelwidth * levelheight * nchannels * typesize);
    gl::glGetTexImage(gl::GLenum(GL_TEXTURE_2D),level,fmt,type,pixels);
    dlog("get_image(GLint,gl::GLenum,gl::GLenum)")
    return pixels;
}

std::vector<std::string> EngGLTexture2D::getLog() { return log.getLog(); }

std::vector<std::string> EngGLTexture2D::getErrLog() {
  return errlog.getLog();
}



void EngGLTexture2D::clear()
{
    log.~Log();
    errlog.~Log();
}

EngGLSampler::EngGLSampler()
{
    texture = NULL;
    unit = 0;
    gl::glGenSamplers(1,&sampler);
}

EngGLSampler::EngGLSampler(const GLint& tu)
{
    texture = NULL;
    unit = tu;
}

void EngGLSampler::setUnit(const GLint& tu)
{
    unit = tu;
}

void EngGLSampler::setUnit(EngGLUniform &uniform,const GLint& tu)
{
    uniform.write(&tu,1,1);
}

void EngGLSampler::property(gl::GLenum prop, GLfloat value)
{
    gl::glSamplerParameterf(sampler,prop,value);
}

void EngGLSampler::property(gl::GLenum prop, GLint value)
{
    gl::glSamplerParameteri(sampler,prop,value);
}

void EngGLSampler::setData(EngGLTexture *datai)
{
    texture = datai;
}

void EngGLSampler::load()
{
    gl::glActiveTexture(gl::GLenum(GL_TEXTURE0 + unit));
    texture->bind();
    gl::glBindSampler(unit,sampler);
}

EngGLSampler::~EngGLSampler()
{
    gl::glDeleteSamplers(1,&sampler);
}
