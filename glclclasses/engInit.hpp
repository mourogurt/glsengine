#ifndef ENGINIT_HPP
#define ENGINIT_HPP
#define GLFW_INCLUDE_GLU
#define GL_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace glm;

#define ENG_INIT_OK 0
#define GLFW_INIT_ERROR 1
#define GLEW_INIT_ERROR 2
#define GLFW_CREATE_WINDOW_ERROR 3
#define ENG_UNKNOW_PLATFORM 4
#define ENG_CONTEXT_ERROR 5

typedef void (*ENG_CL_CALLBACK)(const char *, const void *, size_t, void *);

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

struct EngContextFunct
{
	ENG_CL_CALLBACK func;
};

struct EngPlatform
{
	GLFWwindow* window;
	cl_platform_id* parent_platform;
	cl_device_id* devices;
	cl_uint numDevices;
	cl_context context;
};

class EngInit
{
public:
	EngInit();
	int Init (const char* title, int width = 0, int height = 0);
	cl_uint GetNumPlatforms ();
	cl_int CreateContext (int);
	EngPlatform* GetEngPlatform (int);
	int DestroyContext (int);
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
	void SetCallback (EngContextFunct, void*);
	std::vector<const char*> GetLog();
	std::vector<const char*> GetErrLog();
	void ClearLog();
	void ClearErrLog();
	void SetHint (std::initializer_list<int>);
	void SetHint ();
	void Destroy();
private:
	int ErrFunc (int,const char*);
	bool GLInit;
	bool CLInit;
	GLFWvidmode* vidmode;
	GLFWmonitor* monitor;
	GLFWwindow* window;
	EngLog log;
	EngLog errlog;
	cl_uint numPlatforms;
	std::vector<EngPlatform> platforms;
	EngContextFunct funct;
	void* usr_data;
	cl_platform_id* pltmp;
};
#endif
