#include "engInit.hpp"
#include <cstdio>
#include <iostream>

InitGLClass initgl;

void error_callback	(int error, const char* description)
{
	fputs(description, stderr);
}

int main(int argc, char **argv)
{
	std::vector<const char*> log;
	initgl.SetHint({GLFW_SAMPLES,4,GLFW_CONTEXT_VERSION_MAJOR,4,GLFW_CONTEXT_VERSION_MINOR,2,GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE});
	EngErrFunct f1;
	f1.func = error_callback;
	initgl.SetCallback (f1); 
	initgl.InitGL("Example1",800,640);
	GLFWwindow* window = initgl.GetWindow();
	log = initgl.GetErrLog();
	for (auto p = log.begin(); p!=log.end(); ++p)
		std::cerr<<*p<<std::endl; 
	glClearColor(0.0f,0.0f,1.0f, 0.0f);
	while (glfwGetKey(window,GLFW_KEY_ESC) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	std::cout<<"All is good\n"; 
	return 0;
}