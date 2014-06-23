#version 330 core

in vec4 vcolor;
out vec4 fcolor;

void main(void)
{
    gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
    fcolor = vcolor;
}
