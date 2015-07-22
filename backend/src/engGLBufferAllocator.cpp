#include "engGLBufferAllocator.hpp"

std::vector<EngGLPage*> EngGLBufferAllocator::pages;
std::queue<unsigned> EngGLBufferAllocator::to_delete;
Log EngGLBufferAllocator::log;
Log EngGLBufferAllocator::errlog;
GLsizeiptr EngGLBufferAllocator::pagesize = 1024*1024;
GLsizeiptr EngGLBufferAllocator::cursize = 0;
GLsizeiptr EngGLBufferAllocator::maxsize = 100*1024*1024;

EngGLBuffer::EngGLBuffer(unsigned ida,GLuint pageida,GLsizeiptr sizea,GLintptr offseta)
{
    id = ida;
    pageid = pageida;
    size = sizea;
    offset = offseta;
}

unsigned EngGLBuffer::getID()
{
    return id;
}

GLuint EngGLBuffer::getPageID()
{
    return pageid;
}

GLsizeiptr EngGLBuffer::getBufSize()
{
    return size;
}

GLintptr EngGLBuffer::getOffset()
{
    return offset;
}

gl::GLenum EngGLBuffer::copy(EngGLBuffer* buffera, GLsizei sizea, GLintptr readoffseta, GLintptr writeoffseta)
{
    if (writeoffseta+sizea > size) return gl::GLenum(GL_INVALID_VALUE);
    if (readoffseta+sizea > buffera->getBufSize()) return gl::GLenum(GL_INVALID_VALUE);
    gl::glCopyNamedBufferSubData(buffera->getPageID(),pageid,buffera->getOffset()+readoffseta,offset+writeoffseta,sizea);
    return gl::glGetError();
}

gl::GLenum EngGLBuffer::read(GLvoid* data,GLsizeiptr sizea , GLintptr offseta)
{
    if (sizea+offseta > size) return gl::GLenum(GL_INVALID_VALUE);
    gl::glGetNamedBufferSubData(pageid,offset+offseta,sizea,data);
    return gl::glGetError();
}

gl::GLenum EngGLBuffer::clear(GLvoid* data,gl::GLenum iformata, gl::GLenum formata, gl::GLenum typea,GLsizeiptr sizea , GLintptr offseta)
{
    if (sizea+offseta > size) return gl::GLenum(GL_INVALID_VALUE);
    gl::glClearNamedBufferSubData(pageid,iformata,offset+offseta,sizea,formata,typea,data);
    return gl::glGetError();
}

gl::GLenum EngGLBuffer::write(GLvoid* data,GLsizeiptr sizea , GLintptr offseta)
{
    if (sizea+offseta > size) return gl::GLenum(GL_INVALID_VALUE);
    gl::glNamedBufferSubData(pageid,offset+offseta,sizea,data);
    return gl::glGetError();
}

void EngGLBufferAllocator::setParams(const GLsizeiptr pagesizea,const GLsizeiptr maxsizea)
{
    pagesize = pagesizea;
    maxsize = maxsizea;
}

EngGLBuffer* EngGLBufferAllocator::allocateImmut(GLsizeiptr size,unsigned flags, bool immutable,
                                                       bool force, gl::GLenum &err)
{
    bool find = false;
    int id = 0;
    if (!force)
        for (auto page : pages)
        {
            //TODO: find deleted memory to not move offset(or use defrag, not sure, optional)
            if ((page->flags == flags) &&((page->size - page->offset)>=size) && (page->immutable == immutable))
            {
                find = true;
                break;
            }
            id++;
        }
    if ((!find) || (force))
    {
        GLsizeiptr actualsize = pagesize;
        while (size > actualsize)
            actualsize*=2;
        if (actualsize + cursize > maxsize)
        {
            if(size + cursize <= maxsize)
                actualsize = size;
            else
            {
                //TODO: garbage collector
                //TODO: defrag memory(add some api to query new strides and offset after defrag(when pipeline will be finished))
                dlog("Add errlog");
                errlog.writeLog(std::string("Page creating failed with error:" +
                                            std::to_string(static_cast<int>(GL_OUT_OF_MEMORY))));
                err = gl::GLenum(GL_OUT_OF_MEMORY);
                return NULL;
            }
        }
        cursize+=actualsize;
        EngGLPage* page = new EngGLPage;
        gl::glCreateBuffers(1,&page->id);
        if (immutable)
            gl::glNamedBufferStorage(page->id,actualsize,NULL,gl::BufferStorageMask(flags));
        else
            gl::glNamedBufferData(page->id,size,NULL,gl::GLenum(flags));
        page->immutable = immutable;
        err = gl::glGetError();
        if (err != gl::GLenum(GL_NO_ERROR))
        {
            dlog("Add errlog");
            errlog.writeLog(std::string("Page creating failed with error:" +
                                        std::to_string(static_cast<int>(err))));
            return NULL;
        }
        page->flags = flags;
        page->offset = 0;
        page->size = actualsize;
        if (to_delete.size() == 0)
        {
            pages.push_back(page);
            id = pages.size() - 1;
        } else
        {
            id = to_delete.front();
            to_delete.pop();
            pages[id] = page;
        }
    }
    EngGLBuffer* outbuffer;
    if (pages[id]->to_delete.size() == 0)
    {
        outbuffer = new EngGLBuffer(pages[id]->buf_using.size(),pages[id]->id,size,pages[id]->offset);
        pages[id]->buf_using.push_back(outbuffer);
    } else
    {
        unsigned number = pages[id]->to_delete.front();
        pages[id]->to_delete.pop();
        outbuffer = new EngGLBuffer(number,pages[id]->id,size,pages[id]->offset);
        pages[id]->buf_using[number] = outbuffer;
    }
    pages[id]->offset+=size;
    return outbuffer;
}

void EngGLBufferAllocator::clearAll()
{
    for (auto page : pages)
    {
        if (page != NULL)
        {
            for (auto buffer : page->buf_using)
            {
                if (buffer != NULL)
                    delete buffer;
            }
            page->buf_using.clear();
            gl::glDeleteBuffers(1,&page->id);
        }
    }
    pages.clear();
    to_delete = std::queue<unsigned>();
}

