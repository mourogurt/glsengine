#include "engObject.hpp"
#include <iostream>
void EngObject::init()
{
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 7; i++)
        shader.created_stages[i] = 0;
    log.writeLog(std::string("init() OK"));
}

unsigned int EngObject::loadData(void *buffer, unsigned int cpu_size, unsigned int number, GLenum type, GLenum usage, GLenum format, GLboolean normalized, GLint size)
{
    EngData* tmpdata = new EngData;
    tmpdata->cpu_data = new char[cpu_size];
    memcpy(tmpdata->cpu_data,buffer,cpu_size);
    tmpdata->type = type;
    tmpdata->cpu_data_size = cpu_size;
    tmpdata->usage = usage;
    tmpdata->format = format;
    tmpdata->normalized = normalized;
    tmpdata->size = size;
    tmpdata->num_var = number;
    tmpdata->created_gpu = 0;
    datas.push_back(tmpdata);
    log.writeLog(std::string("loadData(void*,unsigned int,unsigned int,GLenum,GLenum,GLenum,GLboolean,GLint) OK"));
    return datas.size() - 1;
}

void EngObject::loadShader(std::string source, GLenum type)
{
    if (type == GL_VERTEX_SHADER)
        shader.sources[0] = source;
    else if (type == GL_TESS_CONTROL_SHADER)
        shader.sources[1] = source;
    else if (type == GL_TESS_EVALUATION_SHADER)
        shader.sources[2] = source;
    else if (type == GL_GEOMETRY_SHADER)
        shader.sources[3] = source;
    else if (type == GL_FRAGMENT_SHADER)
        shader.sources[4] = source;
    else if (type == GL_COMPUTE_SHADER)
        shader.sources[5] = source;
    log.writeLog(std::string("loadShader(std::string,GLenum) OK"));
}

unsigned int EngObject::loadShaderVar(std::string name,GLenum type)
{
    EngShaderVar* tmpvar;
    tmpvar = new EngShaderVar;
    tmpvar->name = new char [name.size()];
    memcpy (tmpvar->name,name.c_str(),name.size());
    if (type == GL_ARRAY_BUFFER)
    {
        current_locker->lock(platform->window);
        tmpvar->index = glGetAttribLocation(shader.program,tmpvar->name);
        current_locker->unlock();
    }
    vars.push_back(tmpvar);
    return vars.size() - 1;
}

void EngObject::render ()
{
    glUseProgram(shader.program);
    for (unsigned int i = 0; i < datas.size(); i++)
    {
        if (datas[i]->type == GL_ARRAY_BUFFER)
        {
            glBindBuffer(datas[i]->type,datas[i]->gpu_data);
            glDrawArrays(GL_TRIANGLES,0,datas[i]->cpu_data_size / 3);
            glBindBuffer(datas[i]->type,0);
        }
    }
    glUseProgram(0);
    //TODO A lot
}

void EngObject::clearData(unsigned int number)
{
    if (datas[number] != NULL)
    {
        removeGPUData(number);
        if (datas[number]->cpu_data != NULL)
        {
            char* cpu_data = (char*)datas[number]->cpu_data;
            delete [] cpu_data;
        }
    }
    //TODO: Buffers, Uniforms, Samplers, Textures
    log.writeLog(std::string("clearData(unsigned int) OK"));
}

void EngObject::clearShader(unsigned int type)
{
    removeGPUShader();
    if (type == GL_VERTEX_SHADER)
    {
        shader.sources[0] = std::string("");
    }
    else if (type == GL_TESS_CONTROL_SHADER)
    {
        shader.sources[1] = std::string("");
    }
    else if (type == GL_TESS_EVALUATION_SHADER)
    {
        shader.sources[2] = std::string("");
    }
    else if (type == GL_GEOMETRY_SHADER)
    {
        shader.sources[3] = std::string("");
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        shader.sources[4] = std::string("");
    }
    else if (type == GL_COMPUTE_SHADER)
    {
        shader.sources[5] = std::string("");
    }
    else if (type == GL_PROGRAM)
    {
        for (unsigned int i = 0; i < 6; i++)
        {
            shader.sources[i] = std::string("");
        }
    }
    log.writeLog(std::string("clearShader(unsigned int) OK"));
}

void EngObject::clearShaderVar(unsigned int num)
{
    if (vars[num] -> name != NULL)
        delete vars[num] -> name;
    vars[num] -> index = 0;
    vars[num] -> binding = 0;
}

void EngObject::removeGPUData(unsigned int number)
{
    if (datas[number]->created_gpu)
    {
        current_locker->lock(platform->window);
        glBindBuffer(datas[number]->type,datas[number]->gpu_data);
        glDisableVertexAttribArray(vars[datas[number]->num_var]->index);
        glDeleteBuffers(1,&datas[number]->gpu_data);
        glBindBuffer(datas[number]->type,0);
        current_locker->unlock();
        datas[number]->created_gpu = 0;
    }
    log.writeLog(std::string("removeGPUData(unsigned int) OK"));
}

void EngObject::removeGPUShader()
{
    current_locker->lock(platform->window);
    if (shader.created_stages[0])
    {
        glDeleteShader(shader.vertex_shader);
        shader.created_stages[0] = 0;
    }
    if (shader.created_stages[1])
    {
        glDeleteShader(shader.tess_control_shader);
        shader.created_stages[1] = 0;
    }
    if (shader.created_stages[2])
    {
        glDeleteShader(shader.tess_eval_shader);
        shader.created_stages[2] = 0;
    }
    if (shader.created_stages[3])
    {
        glDeleteShader(shader.geometry_shader);
        shader.created_stages[3] = 0;
    }
    if (shader.created_stages[4])
    {
        glDeleteShader(shader.fragment_shader);
        shader.created_stages[4] = 0;
    }
    if (shader.created_stages[5])
    {
        glDeleteShader(shader.compute_shader);
        shader.created_stages[5] = 0;
    }
    if (shader.created_stages[6])
    {
        glDeleteProgram(shader.program);
        shader.created_stages[6] = 0;
    }
    current_locker->unlock();
    log.writeLog(std::string("removeGPUShader() OK"));
}

void EngObject::removeData(unsigned int num)
{
    removeGPUData(num);
    clearData(num);
    delete datas[num];
    datas.erase(datas.begin() + num);
    log.writeLog(std::string("removeData(unsigned int) OK"));
}

void EngObject::removeShaderVar(unsigned int num)
{
    clearShaderVar(num);
    delete vars[num];
    vars.erase(vars.begin() + num);
    log.writeLog(std::string("removeShaderVar(unsigned int) OK"));
}

unsigned int EngObject::createGPUData(unsigned int num)
{
    removeGPUData(num);
    if (datas[num]->type == GL_ARRAY_BUFFER)
    {
        current_locker->lock(platform->window);
        glGenBuffers(1,&datas[num]->gpu_data);
        glBindBuffer(datas[num]->type,datas[num]->gpu_data);
        glBufferData(datas[num]->type,datas[num]->cpu_data_size,datas[num]->cpu_data,datas[num]->usage);
        glVertexAttribPointer(vars[datas[num]->num_var]->index,datas[num]->size,datas[num]->format,datas[num]->normalized,0,NULL);
        glEnableVertexAttribArray(vars[datas[num]->num_var]->index);
        glBindBuffer(datas[num]->type,0);
        current_locker->unlock();
        datas[num]->created_gpu = 1;
    }
    //TODO: Uniforms, Buffers, Samplers, Textures
    log.writeLog(std::string("createGPUData(unsigned int) OK"));
    return 0; // TODO : Errors
}

unsigned int EngObject::createGPUShader()
{
    removeGPUShader();
    current_locker->lock(platform->window);
    GLint resultsh = 0;
    if (shader.sources[0].size() > 0)
    {
        shader.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        char const* source_pointer = shader.sources[0].c_str();
        glShaderSource(shader.vertex_shader,1,&source_pointer,NULL);
        glCompileShader(shader.vertex_shader);
        glGetShaderiv(shader.vertex_shader, GL_COMPILE_STATUS, &resultsh);
        if (resultsh == GL_FALSE)
        {
            GLint info = 0;
            glGetShaderiv(shader.vertex_shader, GL_INFO_LOG_LENGTH, &info);
            GLchar info_mess[info];
            glGetShaderInfoLog(shader.vertex_shader, info, NULL, info_mess);
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string(info_mess));
            shader.created_stages[0] = 0;
            glDeleteShader(shader.vertex_shader);
            return resultsh;
        }
        else
            shader.created_stages[0] = 1;
    } else shader.created_stages[0] = 0;
    if (shader.sources[1].size() > 0)
    {
        shader.tess_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
        char const* source_pointer = shader.sources[1].c_str();
        glShaderSource(shader.tess_control_shader,1,&source_pointer,NULL);
        glCompileShader(shader.tess_control_shader);
        glGetShaderiv(shader.tess_control_shader, GL_COMPILE_STATUS, &resultsh);
        if (resultsh == GL_FALSE)
        {
            GLint info;
            glGetShaderiv(shader.tess_control_shader, GL_INFO_LOG_LENGTH, &info);
            GLchar info_mess[info];
            glGetShaderInfoLog(shader.tess_control_shader, info, NULL, info_mess);
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string(info_mess));
            shader.created_stages[1] = 0;
            glDeleteShader(shader.tess_control_shader);
            return resultsh;
        }
        else
            shader.created_stages[1] = 1;
    } else shader.created_stages[1] = 0;
    if (shader.sources[2].size() > 0)
    {
        shader.tess_eval_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
        char const* source_pointer = shader.sources[2].c_str();
        glShaderSource(shader.tess_eval_shader,1,&source_pointer,NULL);
        glCompileShader(shader.tess_eval_shader);
        glGetShaderiv(shader.tess_eval_shader, GL_COMPILE_STATUS, &resultsh);
        if (resultsh == GL_FALSE)
        {
            GLint info;
            glGetShaderiv(shader.tess_eval_shader, GL_INFO_LOG_LENGTH, &info);
            GLchar info_mess[info];
            glGetShaderInfoLog(shader.tess_eval_shader, info, NULL, info_mess);
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string(info_mess));
            shader.created_stages[2] = 0;
            glDeleteShader(shader.tess_eval_shader);
            return resultsh;
        }
        else
            shader.created_stages[2] = 1;
    } else shader.created_stages[2] = 0;
    if (shader.sources[3].size() > 0)
    {
        shader.geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
        char const* source_pointer = shader.sources[3].c_str();
        glShaderSource(shader.geometry_shader,1,&source_pointer,NULL);
        glCompileShader(shader.geometry_shader);
        glGetShaderiv(shader.geometry_shader, GL_COMPILE_STATUS, &resultsh);
        if (resultsh == GL_FALSE)
        {
            GLint info;
            glGetShaderiv(shader.geometry_shader, GL_INFO_LOG_LENGTH, &info);
            GLchar info_mess[info];
            glGetShaderInfoLog(shader.geometry_shader, info, NULL, info_mess);
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string(info_mess));
            shader.created_stages[3] = 0;
            glDeleteShader(shader.geometry_shader);
            return resultsh;
        }
        else
            shader.created_stages[3] = 1;
    } else shader.created_stages[3] = 0;
    if (shader.sources[4].size() > 0)
    {
        shader.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        char const* source_pointer = shader.sources[4].c_str();
        glShaderSource(shader.fragment_shader,1,&source_pointer,NULL);
        glCompileShader(shader.fragment_shader);
        glGetShaderiv(shader.fragment_shader, GL_COMPILE_STATUS, &resultsh);
        if (resultsh == GL_FALSE)
        {
            GLint info;
            glGetShaderiv(shader.fragment_shader, GL_INFO_LOG_LENGTH, &info);
            GLchar info_mess[info];
            glGetShaderInfoLog(shader.fragment_shader, info, NULL, info_mess);
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string(info_mess));
            shader.created_stages[4] = 0;
            glDeleteShader(shader.fragment_shader);
            return resultsh;
        }
        else
            shader.created_stages[4] = 1;
    } else shader.created_stages[4] = 0;
    if (shader.sources[5].size() > 0)
    {
        shader.compute_shader = glCreateShader(GL_COMPUTE_SHADER);
        char const* source_pointer = shader.sources[5].c_str();
        glShaderSource(shader.compute_shader,1,&source_pointer,NULL);
        glCompileShader(shader.compute_shader);
        glGetShaderiv(shader.compute_shader, GL_COMPILE_STATUS, &resultsh);
        if (resultsh == GL_FALSE)
        {
            GLint info;
            glGetShaderiv(shader.compute_shader, GL_INFO_LOG_LENGTH, &info);
            GLchar info_mess[info];
            glGetShaderInfoLog(shader.compute_shader, info, NULL, info_mess);
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string(info_mess));
            shader.created_stages[5] = 0;
            glDeleteShader(shader.compute_shader);
            return resultsh;
        }
        else
            shader.created_stages[5] = 1;
    } else shader.created_stages[5] = 0;
    shader.program = glCreateProgram();
    if (shader.created_stages[0])
        glAttachShader(shader.program,shader.vertex_shader);
    if (shader.created_stages[1])
        glAttachShader(shader.program,shader.tess_control_shader);
    if (shader.created_stages[2])
        glAttachShader(shader.program,shader.tess_eval_shader);
    if (shader.created_stages[3])
        glAttachShader(shader.program,shader.geometry_shader);
    if (shader.created_stages[4])
        glAttachShader(shader.program,shader.fragment_shader);
    if (shader.created_stages[5])
        glAttachShader(shader.program,shader.compute_shader);
    glLinkProgram(shader.program);
    GLint resultpm;
    glGetProgramiv(shader.program, GL_LINK_STATUS, &resultpm);
    if (resultpm == GL_FALSE)
    {
        GLint info = 0;
        glGetProgramiv(shader.program, GL_INFO_LOG_LENGTH, &info);
        GLchar info_mess[info];
        glGetProgramInfoLog(shader.program, info, NULL, info_mess);
        shader.created_stages[6] = 0;
        removeGPUShader();
        glDeleteProgram(shader.program);
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(std::string(info_mess));
        return resultpm;
    }
    else
        shader.created_stages[6] = 1;
    current_locker->unlock();
    log.writeLog(std::string("createGPUShader() OK"));
    return 0;
}

void EngObject::writeData(void *data, unsigned int cpu_size, unsigned int number, unsigned int var_num, GLenum type, GLenum usage, GLenum format, GLboolean normalized, GLint size, GLboolean to_gpu)
{
    clearData(number);
    datas[number]->cpu_data = new char[cpu_size];
    memcpy (datas[number]->cpu_data,data,cpu_size);
    datas[number]->type = type;
    datas[number]->cpu_data_size = cpu_size;
    datas[number]->usage = usage;
    datas[number]->format = format;
    datas[number]->normalized = normalized;
    datas[number]->size = size;
    datas[number]->num_var = var_num;
    if (to_gpu)
    {
        removeGPUData(number);
        createGPUData(number);
    }
    //TODO: Uniforms, Buffers, Samplers, Textures
    //Optimization require for dynamic draw
    log.writeLog(std::string("loadData(void*,unsigned int,unsigned int,unsigned int,GLenum,GLenum,GLenum,GLboolean,GLint,GLboolean) OK"));
}

void EngObject::writeShader(std::string source, GLenum type, GLboolean to_gpu)
{
    if (type == GL_VERTEX_SHADER)
        shader.sources[0] = source;
    else if (type == GL_TESS_CONTROL_SHADER)
        shader.sources[1] = source;
    else if (type == GL_TESS_EVALUATION_SHADER)
        shader.sources[2] = source;
    else if (type == GL_GEOMETRY_SHADER)
        shader.sources[3] = source;
    else if (type == GL_FRAGMENT_SHADER)
        shader.sources[4] = source;
    else if (type == GL_COMPUTE_SHADER)
        shader.sources[5] = source;
    if (to_gpu)
    {
        removeGPUShader();
        createGPUShader();
    }
    log.writeLog(std::string("writeShader(std::string,GLenum,GLboolean) OK"));
}

std::vector<std::string> EngObject::getLog()
{
    return log.getLog();
}


std::vector<std::string> EngObject::getErrLog()
{
    return errlog.getLog();
}

void EngObject::setController(ContextMutex *controller)
{
    current_locker = controller;
}

void EngObject::setPlatform(EngPlatform *platformin)
{
    platform = platformin;
}


void EngObject::clearAll()
{
    for (unsigned int i = 0; i < datas.size(); i++)
        removeData(i);
    for (unsigned int i = 0; i < vars.size(); i++)
        removeShaderVar(i);
    removeGPUShader();
    clearShader(GL_PROGRAM);
}
