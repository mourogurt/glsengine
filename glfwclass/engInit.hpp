#ifndef GL_ENG_INIT
#define GL_ENG_INIT
#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <CL/cl.h>
#include <cstdlib>
#include <vector>
#include <sstream>

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
	GLFWvidmode* vidmode;
	GLFWmonitor* monitor;
	GLFWwindow* window;
	EngLog log;
	EngLog errlog;
};

struct EngDevice
{ 
	cl_platform_id* parent_platform;
	std::vector<cl_device_id> devices;
};

class InitCLClass
{
public:
	int InitCL(InitGLClass*);
	InitCLClass ();
	std::vector<const char*> GetLog();
	std::vector<const char*> GetErrLog();
	~InitCLClass();
private:
	bool ErrCLFunc (cl_int,const char*);
	EngLog log;
	EngLog errlog;
	cl_uint numContexts;
	cl_uint numPropereties;
	std::vector<cl_uint> numDevices;
	std::vector<cl_context_properties[4]> propereties;
	std::vector<cl_platform_id> platforms;
	std::vector<EngDevice> devices;
	std::vector<cl_context> context;
	InitGLClass* parent;
};
#endif