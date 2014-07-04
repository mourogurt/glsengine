#include "engData.hpp"

EngGLvalue::EngGLvalue()
{
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    length = 0;
    name = NULL;
    #ifdef _DEBUG
    log.writeLog("EngGLData() OK");
    #endif
}

void EngGLvalue::setLength(GLuint lengthi)
{
    length = lengthi;
    #ifdef _DEBUG
    log.writeLog("setLength(GLuint) OK");
    #endif
}

void EngGLvalue::setName(const char* namei)
{
    name.reset(nullptr);
    name = std::unique_ptr<char[]>(new char[strlen(namei)+1]);
    strcpy(name.get(),namei);
    #ifdef _DEBUG
    log.writeLog("setName(char*) OK");
    #endif
}

void EngGLvalue::setProgram(GLuint programi)
{
    program = programi;
    #ifdef _DEBUG
    log.writeLog("setProgram(GLuint) OK");
    #endif
}

std::vector<std::string> EngGLvalue::getLog()
{
    return log.getLog();
}

std::vector<std::string> EngGLvalue::getErrLog()
{
    return errlog.getLog();
}

void EngGLvalue::clear()
{
    name.reset(nullptr);
    #ifdef _DEBUG
    log.writeLog("clear() OK");
    #endif
}

EngGLvalue::~EngGLvalue()
{
    clear();
}

void EngGLAttribute::bind()
{
    location = glGetAttribLocation(program,name.get());
    if (location == -1)
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Nonexistent location of vertex attribute");
        return;
    }
    #ifdef _DEBUG
    log.writeLog("bind() OK");
    #endif
}

void EngGLAttribute::unbind()
{
    location = -1;
    name.reset(nullptr);
    #ifdef _DEBUG
    log.writeLog("unbind() OK");
    #endif
}


bool EngGLAttribute::write(const GLfloat* data)
{
    if (location == -1)
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Attribute is unbinded");
        return 1;
    }
    if (length == 1)
        glVertexAttrib1fv(location,data); else
    if (length == 2)
        glVertexAttrib2fv(location,data); else
    if (length == 3)
        glVertexAttrib3fv(location,data); else
    if (length == 4)
        glVertexAttrib4fv(location,data); else
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Wrong length parameter");
        return 1;
    }
    return 0;
}

bool EngGLAttribute::write(const GLdouble* data)
{
    if (location == -1)
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Attribute is unbinded");
        return 1;
    }
    if (length == 1)
        glVertexAttrib1dv(location,data); else
    if (length == 2)
        glVertexAttrib2dv(location,data); else
    if (length == 3)
        glVertexAttrib3dv(location,data); else
    if (length == 4)
        glVertexAttrib4dv(location,data); else
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Wrong length parameter");
        return 1;
    }
    return 0;
}

bool EngGLAttribute::write(const GLshort* data)
{
    if (location == -1)
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Attribute is unbinded");
        return 1;
    }
    if (length == 1)
        glVertexAttrib1sv(location,data); else
    if (length == 2)
        glVertexAttrib2sv(location,data); else
    if (length == 3)
        glVertexAttrib3sv(location,data); else
    if (length == 4)
        glVertexAttrib4sv(location,data); else
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Wrong length parameter");
        return 1;
    }
    return 0;
}

EngGLbuffer::EngGLbuffer()
{
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
}
