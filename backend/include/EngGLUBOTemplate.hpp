#ifndef ENGGLUBOTEMPLATE_HPP
#define ENGGLUBOTEMPLATE_HPP

#include <engBuffer.hpp>

template <typename T>
void EngGLUBO::writeUBOScalar(T data, unsigned index)
{
    write(&data,sizeof(T),offsets[index]);
}

template <typename T>
void EngGLUBO::writeUBOVec(T* data, unsigned index, unsigned length)
{
    write(data,sizeof(T) * length,offsets[index]);
}

template <typename T>
void EngGLUBO::writeUBOArr(T* data, unsigned index, unsigned length)
{
    GLuint offset = offsets[index];
    for (unsigned i = 0; i < length; i++)
    {
        write(&data[i],sizeof(T),offset);
        offset += astrides[index];
    }
}

template <typename T>
void EngGLUBO::writeUBOMat(T* data, unsigned index, unsigned n ,unsigned m)
{
    GLuint offset = offsets[index];
    for (unsigned i = 0; i < n; i++)
    {
        write(data + i * m,sizeof(T) * m,offset );
        offset += mstrides[index];
    }
}

template <typename T>
void EngGLUBO::writeUBOVecArr(std::initializer_list<T*> data, unsigned index ,unsigned length)
{
    GLuint offset = offsets[index];
    for (T* x : data)
    {
        write(x,sizeof(T) * length,offset);
        offset += astrides[index];
    }
}

template <typename T>
void EngGLUBO::writeUBOMatArr (std::initializer_list<T*> data, unsigned index, unsigned n ,unsigned m)
{
    GLuint offset = offsets[index];
    for (T* x : data)
    {
        for (unsigned i = 0; i < n; i++)
            write(x + i * m,sizeof(T) * m,offset + mstrides[index] * i);
        offset += astrides[index];
    }
}

#endif // ENGGLUBOTEMPLATE_HPP
