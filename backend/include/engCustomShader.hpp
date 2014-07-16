#ifndef ENGCUSTOMSHADER_HPP
#define ENGCUSTOMSHADER_HPP
#include "engInit.hpp"

class EngCustomShader
{
public:
    EngCustomShader();
    GLuint compileShaderStage (GLuint,std::string);
    GLuint linkShader ();
    void cleanShader ();
    void cleanProgram ();
    void cleanShaderStage (GLuint);
    GLuint getProgramID ();
    std::vector<std::string> getLog();
    std::vector<std::string> getErrLog();
private:
    Log log;
    Log errlog;
    GLuint VStage;
    GLuint TCStage;
    GLuint TEStage;
    GLuint GStage;
    GLuint FStage;
    GLuint CStage;
    GLuint Program;
};

#endif // ENGCUSTOMSHADER_HPP
