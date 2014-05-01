#include "engCustomShader.hpp"
#include <iostream>
#include <string>

EngCustomShader::EngCustomShader()
{
    VStage = 0;
    TCStage = 0;
    TEStage = 0;
    GStage = 0;
    FStage = 0;
    CStage = 0;
    Program = 0;
    log.writeLog(std::string("EngCustomShader() OK"));
}

GLuint EngCustomShader::compileShaderStage(GLuint stage, std::string source)
{
    if (stage == GL_VERTEX_SHADER)
    {
        if (VStage != 0)
            cleanShaderStage(stage);
        VStage = glCreateShader(stage);
        char const* source_pointer = source.c_str();
        glShaderSource (VStage,1,&source_pointer,NULL);
        glCompileShader(VStage);
        {
            GLint result;
            glGetShaderiv(VStage,GL_COMPILE_STATUS,&result);
            if (result == GL_FALSE)
            {
                GLsizei lengthmsg;
                glGetShaderiv (VStage,GL_INFO_LOG_LENGTH,&lengthmsg);
                GLchar *logmsg[lengthmsg];
                glGetShaderInfoLog(VStage,lengthmsg,NULL,(GLchar*)logmsg);
                cleanShaderStage(stage);
                log.writeLog(std::string("Add errlog"));
                errlog.writeLog(std::string((const char*)logmsg));
                return result;
            }
        }
    } else
        if (stage == GL_TESS_CONTROL_SHADER)
        {
            if (TCStage != 0)
                cleanShaderStage(stage);
            TCStage = glCreateShader(stage);
            char const* source_pointer = source.c_str();
            glShaderSource (TCStage,1,&source_pointer,NULL);
            glCompileShader(TCStage);
            {
                GLint result;
                glGetShaderiv(TCStage,GL_COMPILE_STATUS,&result);
                if (result == GL_FALSE)
                {
                    GLsizei lengthmsg;
                    glGetShaderiv (TCStage,GL_INFO_LOG_LENGTH,&lengthmsg);
                    GLchar *logmsg[lengthmsg];
                    glGetShaderInfoLog(TCStage,lengthmsg,NULL,(GLchar*)logmsg);
                    cleanShaderStage(stage);
                    log.writeLog(std::string("Add errlog"));
                    errlog.writeLog(std::string((const char*)logmsg));
                    return result;
                }
            }
        } else
            if (stage == GL_TESS_EVALUATION_SHADER)
            {
                if (TEStage != 0)
                    cleanShaderStage(stage);
                TEStage = glCreateShader(stage);
                char const* source_pointer = source.c_str();
                glShaderSource (TEStage,1,&source_pointer,NULL);
                glCompileShader(TEStage);
                {
                    GLint result;
                    glGetShaderiv(TEStage,GL_COMPILE_STATUS,&result);
                    if (result == GL_FALSE)
                    {
                        GLsizei lengthmsg;
                        glGetShaderiv (TEStage,GL_INFO_LOG_LENGTH,&lengthmsg);
                        GLchar *logmsg[lengthmsg];
                        glGetShaderInfoLog(TEStage,lengthmsg,NULL,(GLchar*)logmsg);
                        cleanShaderStage(stage);
                        log.writeLog(std::string("Add errlog"));
                        errlog.writeLog(std::string((const char*)logmsg));
                        return result;
                    }
                }
            } else
                if (stage == GL_GEOMETRY_SHADER)
                {
                    if (GStage != 0)
                        cleanShaderStage(stage);
                    GStage = glCreateShader(stage);
                    char const* source_pointer = source.c_str();
                    glShaderSource (GStage,1,&source_pointer,NULL);
                    glCompileShader(GStage);
                    {
                        GLint result;
                        glGetShaderiv(GStage,GL_COMPILE_STATUS,&result);
                        if (result == GL_FALSE)
                        {
                            GLsizei lengthmsg;
                            glGetShaderiv (GStage,GL_INFO_LOG_LENGTH,&lengthmsg);
                            GLchar *logmsg[lengthmsg];
                            glGetShaderInfoLog(GStage,lengthmsg,NULL,(GLchar*)logmsg);
                            cleanShaderStage(stage);
                            log.writeLog(std::string("Add errlog"));
                            errlog.writeLog(std::string((const char*)logmsg));
                            return result;
                        }
                    }
                } else
                    if (stage == GL_FRAGMENT_SHADER)
                    {
                        if (FStage != 0)
                            cleanShaderStage(stage);
                        FStage = glCreateShader(stage);
                        char const* source_pointer = source.c_str();
                        glShaderSource (FStage,1,&source_pointer,NULL);
                        glCompileShader(FStage);
                        {
                            GLint result;
                            glGetShaderiv(FStage,GL_COMPILE_STATUS,&result);
                            if (result == GL_FALSE)
                            {
                                GLsizei lengthmsg;
                                glGetShaderiv (FStage,GL_INFO_LOG_LENGTH,&lengthmsg);
                                GLchar *logmsg[lengthmsg];
                                glGetShaderInfoLog(FStage,lengthmsg,NULL,(GLchar*)logmsg);
                                cleanShaderStage(stage);
                                log.writeLog(std::string("Add errlog"));
                                errlog.writeLog(std::string((const char*)logmsg));
                                return result;
                            }
                        }
                    } else
                        if (stage == GL_COMPUTE_SHADER)
                        {
                            if (CStage != 0)
                                cleanShaderStage(stage);
                            CStage = glCreateShader(stage);
                            char const* source_pointer = source.c_str();
                            glShaderSource (CStage,1,&source_pointer,NULL);
                            glCompileShader(CStage);
                            {
                                GLint result;
                                glGetShaderiv(CStage,GL_COMPILE_STATUS,&result);
                                if (result == GL_FALSE)
                                {
                                    GLsizei lengthmsg;
                                    glGetShaderiv (TCStage,GL_INFO_LOG_LENGTH,&lengthmsg);
                                    GLchar *logmsg[lengthmsg];
                                    glGetShaderInfoLog(TCStage,lengthmsg,NULL,(GLchar*)logmsg);
                                    cleanShaderStage(stage);
                                    log.writeLog(std::string("Add errlog"));
                                    errlog.writeLog(std::string((const char*)logmsg));
                                    return result;
                                }
                            }
                        } else
                        {
                            log.writeLog(std::string("Add errlog"));
                            errlog.writeLog(std::string("Unsupported/unknow stage"));
                            return GL_FALSE;
                        }
    log.writeLog(std::string("compileShaderStage(GLuint,std::string) OK"));
    return GL_TRUE;
}

GLuint EngCustomShader::linkShader()
{
    if (Program != 0)
        cleanProgram();
    Program = glCreateProgram();
    if (VStage != 0)
        glAttachShader(Program,VStage);
    if (TCStage != 0)
        glAttachShader(Program,TCStage);
    if (TEStage != 0)
        glAttachShader(Program,TEStage);
    if (GStage != 0)
        glAttachShader(Program,GStage);
    if (FStage != 0)
        glAttachShader(Program,FStage);
    if (CStage != 0)
        glAttachShader(Program,CStage);
    glLinkProgram(Program);
    {
        GLint result;
        glGetProgramiv(Program, GL_LINK_STATUS,&result);
        if (result == GL_FALSE)
        {
            GLsizei lengthmsg;
            glGetProgramiv(Program,GL_INFO_LOG_LENGTH,&lengthmsg);
            GLchar *logmsg[lengthmsg];
            glGetShaderInfoLog(Program,lengthmsg,NULL,(GLchar*)logmsg);
            cleanProgram();
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string((const char*)logmsg));
            return GL_FALSE;
        }
    }
    log.writeLog(std::string("linkShader() OK"));
    return GL_TRUE;
}

void EngCustomShader::cleanShader()
{
    if (Program != 0)
        cleanProgram();
    if (CStage != 0)
        cleanShaderStage(GL_COMPUTE_SHADER);
    if (FStage != 0)
        cleanShaderStage(GL_FRAGMENT_SHADER);
    if (GStage != 0)
        cleanShaderStage(GL_GEOMETRY_SHADER);
    if (TEStage != 0)
        cleanShaderStage(GL_TESS_EVALUATION_SHADER);
    if (TCStage != 0)
        cleanShaderStage(GL_TESS_CONTROL_SHADER);
    if (VStage != 0)
        cleanShaderStage(GL_VERTEX_SHADER);
    log.writeLog(std::string("cleanShader() OK"));
}

void EngCustomShader::cleanProgram()
{
    glDeleteProgram(Program);
    Program = 0;
    log.writeLog(std::string("cleanProgram() OK"));
}

void EngCustomShader::cleanShaderStage(GLuint stage)
{
    if (stage == GL_COMPUTE_SHADER)
    {
        glDeleteShader(CStage);
        CStage = 0;
    } else  if (stage == GL_FRAGMENT_SHADER)
    {
        glDeleteShader(FStage);
        FStage = 0;
    } else if (stage == GL_GEOMETRY_SHADER)
    {
        glDeleteShader(GStage);
        GStage = 0;
    } else if (stage == GL_TESS_EVALUATION_SHADER)
    {
        glDeleteShader(TEStage);
        TEStage = 0;
    } else if (stage == GL_TESS_CONTROL_SHADER)
    {
        glDeleteShader(TCStage);
        TCStage = 0;
    } else if (stage == GL_VERTEX_SHADER)
    {
        glDeleteShader(VStage);
        VStage = 0;
    }
    log.writeLog(std::string("cleanShaderStage(GLuint)OK"));
}

GLuint EngCustomShader::getProgramID()
{
    log.writeLog(std::string("getProgramID()OK"));
    return Program;
}

std::vector<std::string> EngCustomShader::getLog()
{
    return log.getLog();
}

std::vector<std::string> EngCustomShader::getErrLog()
{
    return errlog.getLog();
}
