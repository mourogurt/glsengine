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

bool EngGLUniform::bind(std::string str)
{
    location = glGetUniformLocation(program,str.c_str());
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

void EngGLUniform::bind(GLint locationi)
{
    location = locationi;
}

void EngGLUniform::setProgram(GLuint programi)
{
    program = programi;
}

bool EngGLUniform::write(const GLfloat *data, unsigned length, GLsizei count)
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
        glUniform1fv(location,count,data); else
    if (length == 2)
        glUniform2fv(location,count,data); else
    if (length == 3)
        glUniform3fv(location,count,data); else
    if (length == 4)
        glUniform4fv(location,count,data); else
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Wrong length parameter");
        return 1;
    }
    #ifdef _DEBUG
    log.writeLog(std::string("write(const GLfloat*,unsigned,GLsizei) OK"));
    #endif
    return 0;
}

bool EngGLUniform::write(const GLint *data, unsigned length, GLsizei count)
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
        glUniform1iv(location,count,data); else
    if (length == 2)
        glUniform2iv(location,count,data); else
    if (length == 3)
        glUniform3iv(location,count,data); else
    if (length == 4)
        glUniform4iv(location,count,data); else
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Wrong length parameter");
        return 1;
    }
    #ifdef _DEBUG
    log.writeLog(std::string("write(const GLint*,unsigned,GLsizei) OK"));
    #endif
    return 0;
}

bool EngGLUniform::write(const GLuint *data, unsigned length, GLsizei count)
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
        glUniform1uiv(location,count,data); else
    if (length == 2)
        glUniform2uiv(location,count,data); else
    if (length == 3)
        glUniform3uiv(location,count,data); else
    if (length == 4)
        glUniform4uiv(location,count,data); else
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Wrong length parameter");
        return 1;
    }
    #ifdef _DEBUG
    log.writeLog(std::string("write(const GLuint*,unsigned,GLsizei) OK"));
    #endif
    return 0;
}

bool EngGLUniform::write(const GLfloat *data, unsigned rows, unsigned colums, GLsizei count, GLboolean transpose)
{
    if (location == -1)
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Attribute is unbinded");
        return 1;
    }
    if ((rows == 2) && (colums == 2))
        glUniformMatrix2fv(location,count,transpose,data); else
    if ((rows == 3) && (colums == 3))
        glUniformMatrix3fv(location,count,transpose,data); else
    if ((rows == 4) && (colums == 4))
        glUniformMatrix4fv(location,count,transpose,data); else
    if ((rows == 2) && (colums == 3))
        glUniformMatrix2x3fv(location,count,transpose,data); else
    if ((rows == 3) && (colums == 2))
        glUniformMatrix3x2fv(location,count,transpose,data); else
    if ((rows == 2) && (colums == 4))
        glUniformMatrix2x4fv(location,count,transpose,data); else
    if ((rows == 4) && (colums == 2))
        glUniformMatrix4x2fv(location,count,transpose,data); else
    if ((rows == 3) && (colums == 4))
        glUniformMatrix3x4fv(location,count,transpose,data); else
    if ((rows == 4) && (colums == 3))
        glUniformMatrix4x3fv(location,count,transpose,data); else
    {
        #ifdef _DEBUG
        log.writeLog(std::string("Add errlog"));
        #endif
        errlog.writeLog("Wrong rows/colums parameter");
        return 1;
    }
    #ifdef _DEBUG
    log.writeLog(std::string("write(const GLfloat*,unsigned,unsigned,GLsizei,GLboolean) OK"));
    #endif
    return 0;
}

std::vector<std::string> EngGLUniform::getLog()
{
    return log.getLog();
}

std::vector<std::string> EngGLUniform::getErrLog()
{
    return errlog.getLog();
}
