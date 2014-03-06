#ifndef ENGOBJECT_HPP
#define ENGOBJECT_HPP

#include "engInit.hpp"

struct EngShaderVar
{
    GLchar* name;
    GLuint index;
    GLuint binding;
};

struct EngData
{
    GLuint gpu_data;
    void* cpu_data;
    unsigned int cpu_data_size;
    GLenum type;
    GLenum usage;
    GLenum format;
    GLint size;
    GLboolean normalized;
    bool created_gpu;
    unsigned int num_var;
};

struct EngShader
{
    GLuint program;
    GLuint vertex_shader;
    GLuint geometry_shader;
    GLuint tess_control_shader;
    GLuint tess_eval_shader;
    GLuint compute_shader;
    GLuint fragment_shader;
    std::string sources[6];
    bool created_stages[7];
};

//TODO:
//Binding vars
//OpenCL objects
//Uniform Buffers Samplers Textures


class EngObject
{
public:
    void init();
    unsigned int loadData (void*,unsigned int, unsigned int, GLenum type = GL_ARRAY_BUFFER,GLenum usage=GL_STATIC_DRAW, GLenum format = GL_FLOAT, GLboolean normalized = GL_FALSE, GLint size = 4);
    unsigned int loadShaderVar (std::string,GLenum type = GL_ARRAY_BUFFER);
    void loadShader(std::string, GLenum);
    void render ();
    void clearData (unsigned int);
    void clearShaderVar (unsigned int);
    void clearShader (unsigned int);
    void removeGPUData (unsigned int);
    void removeGPUShader ();
    void removeData (unsigned int);
    void removeShaderVar (unsigned int);
    unsigned int createGPUData (unsigned int);
    unsigned int createGPUShader ();
    void writeData (void*,unsigned int,unsigned int, unsigned int,GLenum type = GL_ARRAY_BUFFER,GLenum usage = GL_STATIC_DRAW, GLenum format = GL_FLOAT, GLboolean normalized = GL_FALSE, GLint size = 4, GLboolean to_gpu = GL_TRUE);
    void writeShader (std::string,GLenum,GLboolean to_gpu = GL_TRUE);
    std::vector<std::string> getLog ();
    std::vector<std::string> getErrLog ();
    void setPlatform (EngPlatform*);
    void setController (ContextMutex*);
    void clearAll ();
private:
    std::vector<EngData*> datas;
    std::vector<EngShaderVar*> vars;
    EngShader shader;
    Log log;
    Log errlog;
    ContextMutex* current_locker;
    EngPlatform *platform;
    GLuint VAO;
};

#endif // ENGOBJECT_HPP
