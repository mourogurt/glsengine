#ifndef GL_ENG_INIT
#define GL_ENG_INIT
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <CL/cl.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <functional>

using namespace glm;

#define ENG_INIT_OK 0;
#define GLFW_INIT_ERROR 1
#define GLEW_INIT_ERROR 2
#define GLFW_CREATE_WINDOW_ERROR 3

class EngLog
{
public:
	std::vector<const char*> GetLog();
	void WriteLog (const char*);
	void ClearLog();
	~EngLog();
private:
	std::vector <const char*> log;
};

struct EngErrFunct
{
	GLFWerrorfun func;
};

struct EngWinPosFunct
{
	GLFWwindowposfun func;
};

struct EngWinSizeFunct
{
	GLFWwindowsizefun func;
};

struct EngWinCloseFunct
{
	GLFWwindowclosefun func;
};

struct EngWinRefFunct
{
	GLFWwindowrefreshfun func;
};

struct EngWinFocFunct
{
	GLFWwindowfocusfun func;
};

struct EngWinIconFunct
{
	GLFWwindowiconifyfun func;
};

struct EngMouseButFunct
{
	GLFWmousebuttonfun func;
};

struct EngCurPosFunct
{
	GLFWcursorposfun func;
};

struct EngCurEnterFunct
{
	GLFWcursorenterfun func;
};

struct EngScrollFunct
{
	GLFWscrollfun func;
};

struct EngKeyFunct
{
	GLFWkeyfun func;
};

struct EngCharFunct
{
	GLFWcharfun func;
};

struct EngMonitorFunct
{
	GLFWmonitorfun func;
};

class InitGLClass
{
public:
	InitGLClass();
	int InitGL(const char*);
	int InitGL(const char*,int,int);
	void SetCallback (EngErrFunct);
	void SetCallback (EngWinPosFunct);
	void SetCallback (EngWinSizeFunct);
	void SetCallback (EngWinCloseFunct);
	void SetCallback (EngWinRefFunct);
	void SetCallback (EngWinFocFunct);
	void SetCallback (EngWinIconFunct);
	void SetCallback (EngMouseButFunct);
	void SetCallback (EngCurPosFunct);
	void SetCallback (EngCurEnterFunct);
	void SetCallback (EngScrollFunct);
	void SetCallback (EngKeyFunct);
	void SetCallback (EngCharFunct);
	void SetCallback (EngMonitorFunct);
	std::vector<const char*> GetLog();
	std::vector<const char*> GetErrLog();
	GLFWwindow* GetWindow();  //remove later
	void SetHint (std::initializer_list<int>);
	void SetHint ();
	void DestroyGL();
	~InitGLClass();
private:
	bool Init;
	GLFWvidmode vidmode;
	GLFWmonitor* monitor;
	GLFWwindow* window;
	EngLog log;
	EngLog errlog;
};

class InitCLClass
{
public:
	int InitCL(InitGLClass);
	InitGLClass InitCL();
	InitCLClass ();
	std::vector<const char*> GetLog();
	~InitCLClass();
private:
	EngLog log;
	cl_uint numPlatforms;
	cl_uint numDevices
	std::vector<cl_platform_id> platforms;
	std::vector<cl_device_id> devices;
	cl_context context;
};
#endif