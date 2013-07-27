#include "engCompute.hpp"
#include <cstring>
#include <iostream>

EngComputeArray::EngComputeArray()
{
    sources.clear();
    programs.clear();
    log.clearLog();
    errlog.clearLog();
    log.writeLog("EngComputeArray() OK");
}

void* EngComputeArray::addCompute(EngLoadCompFunct funct, void *in)
{
    EngCompute tmp;
    void* out = nullptr;
    tmp = funct.func(in,out);
    sources.push_back(tmp);
    log.writeLog("addCompute(EngLoadCompFunct,void*) OK");
    return out;
}

void EngComputeArray::deleteCompute(size_t num)
{
    size_t i = 0;
    size_t t = 0;
    clearSource(num);
    if (num == 0)
        sources.pop_front();
    else if (num == sources.size())
        sources.pop_back();
    else
        for (i = 0; i < sources.size(); i++, t++)
        {
            sources[t] = sources[i];
            if (t == num) t--;
        }
    log.writeLog("deleteCompute(int) OK");
}

void EngComputeArray::deleteProgram(size_t num)
{
    size_t i = 0;
    size_t t = 0;
    clearProgram(num);
    if (num == 0)
        programs.pop_front();
    else if (num == programs.size())
        programs.pop_back();
    else
        for (i = 0; i < programs.size(); i++, t++)
        {
            programs[t] = programs[i];
            if (t == num) t--;
        }
    log.writeLog("deleteProgram(size_t) OK");
}

size_t EngComputeArray::getNumSources()
{
    return sources.size();
}

size_t EngComputeArray::getNumPrograms()
{
    return programs.size();
}

GLuint EngComputeArray::getProgram(int num)
{
    log.writeLog("getProgram(int) OK");
    return programs.at(num);
}

int EngComputeArray::createProgram(int num)
{
    int err;
    GLuint VertexShaderID = 0, FragmentShaderID = 0;
    int InfoLogLength;
    GLuint ProgramID = glCreateProgram();
    if (strcmp(sources[num].vertex_source,"") != 0)
    {
        VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        char const* VertexSourcePointer = sources[num].vertex_source;
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
        glCompileShader(VertexShaderID);
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &err);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            char* VertexShaderErrorMessage = new char[InfoLogLength];
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
            std::string str;
            for (int i = 0; i < InfoLogLength; i++)
            {
                str.push_back(VertexShaderErrorMessage[i]);
            }
            str+='\0';
            log.writeLog("Add errlog");
            errlog.writeLog(str.c_str());
            delete [] VertexShaderErrorMessage;
            glDeleteShader(VertexShaderID);
            glDeleteProgram(ProgramID);
            return err;
        }
        glAttachShader(ProgramID, VertexShaderID);
    }
    if (strcmp(sources[num].fragment_source,"") != 0)
    {
        FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        char const * FragmentSourcePointer = sources[num].fragment_source;
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
        glCompileShader(FragmentShaderID);
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &err);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            char* FragmentShaderErrorMessage = new char[InfoLogLength];
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage);
            std::string str;
            for (int i = 0; i < InfoLogLength; i++)
            {
                str.push_back(FragmentShaderErrorMessage[i]);
            }
            str+='\0';
            log.writeLog("Add errlog");
            errlog.writeLog(str.c_str());
            delete [] FragmentShaderErrorMessage;
            glDeleteShader(FragmentShaderID);
            if (strcmp(sources[num].vertex_source,"") != 0)
                glDeleteShader(VertexShaderID);
            glDeleteProgram(ProgramID);
            return err;
        }
        glAttachShader(ProgramID, FragmentShaderID);
    }
    glLinkProgram(ProgramID);
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &err);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        char* ProgramErrorMessage = new char[InfoLogLength];
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
        std::string str;
        for (int i = 0; i < InfoLogLength; i++)
        {
            str.push_back(ProgramErrorMessage[i]);
        }
        str+='\0';
        log.writeLog("Add errlog");
        errlog.writeLog(str.c_str());
        delete [] ProgramErrorMessage;
        if (strcmp(sources[num].vertex_source,"") != 0)
            glDeleteShader(VertexShaderID);
        if (strcmp(sources[num].fragment_source,"") != 0)
            glDeleteShader(FragmentShaderID);
        glDeleteProgram(ProgramID);
        return err;
    }
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    programs.push_back(ProgramID);
    log.writeLog("createProgram(int,int&) OK");
    return 0;
}

void EngComputeArray::destroy()
{
    for (size_t i = 0; i < programs.size(); i++)
    {
        clearProgram(i);
        clearSource(i);
    }
    sources.clear();
    programs.clear();
    log.clearLog();
    errlog.clearLog();
}

std::vector<const char*> EngComputeArray::getLog()
{
    return log.getLog();
}

std::vector<const char*> EngComputeArray::getErrLog()
{
    return errlog.getLog();
}

void EngComputeArray::clearLog()
{
    log.clearLog();
}

void EngComputeArray::clearErrLog()
{
    errlog.clearLog();
}

void EngComputeArray::clearSource(int num)
{
    if (sources[num].vertex_source != nullptr) delete [] sources[num].vertex_source;
    if (sources[num].fragment_source != nullptr) delete [] sources[num].fragment_source;
    log.writeLog("clearSource(int) OK");
}

void EngComputeArray::clearProgram(int num)
{
    if (programs[num] != 0) glDeleteProgram(programs[num]);
    log.writeLog("clearProgram(int) OK");
}
