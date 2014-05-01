#include "engData.hpp"

EngData::EngData()
{
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
}

void EngData::setName(std::string namei)
{
    name = namei;
}

void EngData::setProgram(GLuint programi)
{
    program = programi;
}

EngData::~EngData()
{
    glDeleteVertexArrays(1,&VAO);
}
