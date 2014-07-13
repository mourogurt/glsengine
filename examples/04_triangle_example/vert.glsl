#version 330 core

attribute vec4 vcolor;
attribute vec3 pos;
out vec4 fcolor;

void main(void)
{
    gl_Position = vec4(pos,1.0f);
    fcolor = vcolor;
}
