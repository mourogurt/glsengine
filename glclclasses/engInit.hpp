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
    std::vector<const char*> getLog();
    void writeLog (const char*);
    void clearLog();
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
    int width;
    int height;
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
    int init (const char* title, int width = 0, int height = 0);
    cl_uint getNumPlatforms ();
    cl_int createContext (int);
    EngPlatform* getEngPlatform (int);
    int destroyContext (int);
    void setCallback (EngErrFunct);
    void setCallback (EngWinPosFunct);
    void setCallback (EngWinSizeFunct);
    void setCallback (EngWinCloseFunct);
    void setCallback (EngWinRefFunct);
    void setCallback (EngWinFocFunct);
    void setCallback (EngWinIconFunct);
    void setCallback (EngMouseButFunct);
    void setCallback (EngCurPosFunct);
    void setCallback (EngCurEnterFunct);
    void setCallback (EngScrollFunct);
    void setCallback (EngKeyFunct);
    void setCallback (EngCharFunct);
    void setCallback (EngMonitorFunct);
    void setCallback (EngContextFunct, void*);
    std::vector<const char*> getLog();
    std::vector<const char*> getErrLog();
    void clearLog();
    void clearErrLog();
    void setHint (std::initializer_list<int>);
    void setHint ();
    void destroy();
private:
    int errFunc (int,const char*);
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
