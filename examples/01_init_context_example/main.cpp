#include <iostream>
#include <engInit.hpp>

using namespace std;

int main()
{
    EngInit init;
    init.setHint({GLFW_VISIBLE,GL_FALSE});
    init.createGLWindow("init gl context",1,1);
    GLint sup_major = 0;
    GLint sup_minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &sup_major);
    glGetIntegerv(GL_MINOR_VERSION, &sup_minor);
    std::cout << "Supported OpenGL version " << sup_major <<'.' << sup_minor << std::endl;
    init.clearALL();
    return 0;
}

