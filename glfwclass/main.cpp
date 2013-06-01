#include "engInit.hpp"
#include <cstdio>
#include <iostream>

void error_callback	(int error, const char* description)
{
	fputs(description, stderr);
}

int main(int argc, char **argv)
{
	std::vector<const char*> log;
	EngInit initclgl;
	initclgl.SetHint({GLFW_SAMPLES,4,GLFW_CONTEXT_VERSION_MAJOR,4,GLFW_CONTEXT_VERSION_MINOR,2,GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE});
	EngErrFunct f1;
	f1.func = error_callback;
	initclgl.SetCallback (f1);
	initclgl.Init("test",800,640);
	std::cout<<"Platforms: "<<initclgl.GetNumPlatforms()<<std::endl;
	initclgl.CreateContext(0);
	EngPlatform* MainPlatform = initclgl.GetEngPlatform(0);
	log = initclgl.GetErrLog();
	std::cout<<"Errors:\n";
	for (auto p = log.begin(); p!=log.end(); ++p)
		std::cerr<<'\t'<<*p<<std::endl;
	initclgl.ClearErrLog();
	std::cout<<"Debug Info:\n";
	log = initclgl.GetLog();
	for (auto p = log.begin(); p!=log.end(); ++p)
		std::cout<<'\t'<<*p<<std::endl;
	initclgl.ClearLog();
	glClearColor(0.0f,0.0f,1.0f, 0.0f);
	while (glfwGetKey(MainPlatform->window,GLFW_KEY_ESC) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(MainPlatform->window);
	}
	initclgl.Destroy();
	return 0;
}