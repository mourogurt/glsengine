#version 330 core

in vec4 vcolor;
in vec4 position;
out vec4 fcolor;

void main(void)
{
    gl_Position = position;
    fcolor = vcolor;
}
