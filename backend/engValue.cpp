#include "engValue.hpp"


bool EngGLAttribute::bind(std::string str)
{
    location = glGetAttribLocation(program,str.c_str());
    if (location == -1)
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Nonexistent location of vertex attribute");
        return 1;
    }
    #ifdef _DEBUG
    log.writeLog("bind(std::string) OK");
    #endif
    return 0;
}

void EngGLAttribute::bind(GLint locationi)
{
    location = locationi;
}

void EngGLAttribute::setProgram(GLuint programi)
{
    program = programi;
}

bool EngGLAttribute::write(const GLfloat* data, unsigned length)
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
    #ifdef _DEBUG
    log.writeLog(std::string("write(const GLfloat*,unsigned) OK"));
    #endif
    return 0;
}

bool EngGLAttribute::write(const GLdouble* data, unsigned length)
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
    #ifdef _DEBUG
    log.writeLog(std::string("write(const GLdouble*,unsigned) OK"));
    #endif
    return 0;
}

bool EngGLAttribute::write(const GLshort* data, unsigned length)
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
    #ifdef _DEBUG
    log.writeLog(std::string("write(const GLshort*,unsigned) OK"));
    #endif
    return 0;
}

std::vector<std::string> EngGLAttribute::getLog()
{
    return log.getLog();
}

std::vector<std::string> EngGLAttribute::getErrLog()
{
    return errlog.getLog();
}
