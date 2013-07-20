#include "engCompute.hpp"
#include <cstring>

EngComputeArray::EngComputeArray()
{
    sources.clear();
    programs.clear();
    log.clearLog();
    errlog.clearLog();
}

void* EngComputeArray::addCompute(EngLoadCompFunct funct, void *in)
{
    EngCompute tmp;
    void* out = nullptr;
    tmp = funct.func(in,out);
    sources.push_back(tmp);
    return out;
}

GLuint EngComputeArray::createProgram(int num, int &err)
{
    GLuint VertexShaderID, FragmentShaderID;
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
            char* VertexShaderErrorMessage = new char[InfoLogLength+1];
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
            log.writeLog("Add errlog");
            errlog.writeLog(VertexShaderErrorMessage);
            delete [] VertexShaderErrorMessage;
            glDeleteShader(VertexShaderID);
            glDeleteProgram(ProgramID);
            return 0;
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
            char* FragmentShaderErrorMessage = new char[InfoLogLength+1];
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage);
            log.writeLog("Add errlog");
            errlog.writeLog(FragmentShaderErrorMessage);
            delete [] FragmentShaderErrorMessage;
            glDeleteShader(FragmentShaderID);
            if (strcmp(sources[num].vertex_source,"") != 0)
                glDeleteShader(VertexShaderID);
            glDeleteProgram(ProgramID);
            return 0;
        }
        glAttachShader(ProgramID, FragmentShaderID);
    }
    glLinkProgram(ProgramID);
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &err);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        char* ProgramErrorMessage = new char[InfoLogLength+1];
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
        log.writeLog("Add errlog");
        errlog.writeLog(ProgramErrorMessage);
        delete [] ProgramErrorMessage;
        if (strcmp(sources[num].vertex_source,"") != 0)
            glDeleteShader(VertexShaderID);
        if (strcmp(sources[num].fragment_source,"") != 0)
            glDeleteShader(FragmentShaderID);
        glDeleteProgram(ProgramID);
        return 0;
    }
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    programs.push_back(ProgramID);
    log.writeLog("createProgram(int,int&) OK");
    return ProgramID;
}

