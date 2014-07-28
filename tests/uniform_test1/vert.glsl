#version 330 core

attribute vec4 vcolor;
attribute vec4 pos;
out vec4 fcolor;
uniform mat4 MVP;

void main(void)
{
    gl_Position = MVP * pos;
    fcolor = vcolor;
}
