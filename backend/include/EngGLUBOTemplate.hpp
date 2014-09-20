#ifndef ENGGLUBOTEMPLATE_HPP
#define ENGGLUBOTEMPLATE_HPP

#include <engBuffer.hpp>

template <typename T>
void EngGLUBO::writeUBOScalar(unsigned index,T data)
{
    write(&data,sizeof(T),offsets[index]);
}

template <typename T>
void EngGLUBO::writeUBOVec(unsigned index, unsigned length,T* data)
{
    write(data,sizeof(T) * length,offsets[index]);
}

template <typename T>
void EngGLUBO::writeUBOArr(unsigned index, unsigned length,T* data)
{
    GLuint offset = offsets[index];
    for (unsigned i = 0; i < length; i++)
    {
        write(&data[i],sizeof(T),offset);
        offset += astrides[index];
    }
}

template <typename T>
void EngGLUBO::writeUBOMat(unsigned index, unsigned n ,unsigned m,T* data)
{
    GLuint offset = offsets[index];
    for (unsigned i = 0; i < n; i++)
    {
        write(data + i * m,sizeof(T) * m,offset );
        offset += mstrides[index];
    }
}

template <typename T>
void EngGLUBO::writeUBOVecArr(unsigned index ,unsigned length, std::initializer_list<T*> data)
{
    GLuint offset = offsets[index];
    for (T* x : data)
    {
        write(x,sizeof(T) * length,offset);
        offset += astrides[index];
    }
}

template <typename T>
void EngGLUBO::writeUBOMatArr (unsigned index, unsigned n ,unsigned m,std::initializer_list<T*> data)
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
