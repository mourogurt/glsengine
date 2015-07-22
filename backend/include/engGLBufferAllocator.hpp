#ifndef ENGGLBUFFERALLOCATOR_HPP
#define ENGGLBUFFERALLOCATOR_HPP
#include <vector>
#include <queue>
#include <algorithm>
#include "engInit.hpp"

//TODO: Add methods to read/write to buffers
//TODO: Add child classes that implement immutable/mutable methods
//TODO: Think about iformat
//TODO: Add logs to buffer
class EngGLBuffer
{
public:
    EngGLBuffer (unsigned,GLuint,GLsizeiptr,GLintptr);
    EngGLBuffer (const EngGLBuffer &) = delete;
    EngGLBuffer& operator= (const EngGLBuffer &) = delete;
    unsigned getID();
    GLuint getPageID();
    GLsizeiptr getBufSize();
    GLintptr getOffset();
    gl::GLenum read(GLvoid* data,GLsizeiptr sizea , GLintptr offseta = 0);
    gl::GLenum clear(GLvoid* data,gl::GLenum iformata ,gl::GLenum formata, gl::GLenum typea, GLsizeiptr sizea , GLintptr offseta = 0);
    gl::GLenum write(GLvoid* data,GLsizeiptr sizea , GLintptr offseta = 0);
    gl::GLenum copy(EngGLBuffer* buffera, GLsizei sizea, GLintptr readoffseta = 0, GLintptr writeoffseta = 0);
private:
    unsigned id;
    GLuint pageid;
    GLsizeiptr size;
    GLintptr offset;
};

struct EngGLPage
{
    GLuint id;
    bool immutable;
    bool mapped;
    unsigned flags;
    GLintptr offset;
    GLsizeiptr size;
    std::vector<EngGLBuffer*> buf_using;
    std::queue<unsigned> to_delete;
};

class EngGLBufferAllocator
{
public:
    static void setParams(const GLsizeiptr pagesizea,const GLsizeiptr maxsizea);
    static EngGLBuffer* allocateImmut(GLsizeiptr size,unsigned flags, bool immutable,
                                            bool force, gl::GLenum &err);
    static void releaseBuffer (const EngGLBuffer* id, gl::GLenum &err);
    static GLvoid* getPagePtr(const EngGLBuffer* id, gl::GLenum &err);
    static GLvoid* getBufPtr(const EngGLBuffer* id, gl::GLenum &err);
    static void unmap (const EngGLBuffer* id);
    static void clearAll();
private:
    static void defrag();
    static void cleanUnused();
private:
    static std::vector<EngGLPage*> pages;
    static std::queue<unsigned> to_delete;
    static Log log;
    static Log errlog;
    static GLsizeiptr pagesize;
    static GLsizeiptr cursize;
    static GLsizeiptr maxsize;


};

#endif // ENGGLBUFFERALLOCATOR_HPP
