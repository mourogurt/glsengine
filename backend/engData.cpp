#include "engData.hpp"

EngGLData::EngGLData()
{
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    length = 0;
    name = NULL;
    #ifdef _DEBUG
    log.writeLog("EngGLData() OK");
    #endif
}

void EngGLData::setLength(GLuint lengthi)
{
    length = lengthi;
    #ifdef _DEBUG
    log.writeLog("setLength(GLuint) OK");
    #endif
}

void EngGLData::setName(const char* namei)
{
    if (name != NULL)
        delete [] name;
    name = new char[strlen(namei)];
    strcpy(name,namei);
    #ifdef _DEBUG
    log.writeLog("setName(char*) OK");
    #endif
}

void EngGLData::setProgram(GLuint programi)
{
    program = programi;
    #ifdef _DEBUG
    log.writeLog("setProgram(GLuint) OK");
    #endif
}

std::vector<std::string> EngGLData::getLog()
{
    return log.getLog();
}

std::vector<std::string> EngGLData::getErrLog()
{
    return errlog.getLog();
}

EngGLData::~EngGLData()
{
    glDeleteVertexArrays(1,&VAO);
    if (name!=NULL)
        delete [] name;
}

void EngAttribute::bind()
{
    location = glGetAttribLocation(program,name);
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

void EngAttribute::write(const GLfloat* data)
{
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
        return;
    }
    #ifdef _DEBUG
    log.writeLog("write(GLfloat*) OK");
    #endif
}

void EngAttribute::clear()
{
    length = 0;
    if (name != NULL)
        delete [] name;
    #ifdef _DEBUG
    log.writeLog("clear() OK");
    #endif
}
