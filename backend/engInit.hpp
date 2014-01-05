#ifndef ENGINIT_HPP
#define ENGINIT_HPP
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GLFW/glfw3.h>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <cstdlib>
#include <vector>
#include <sstream>
#include "../system/log.h"

#define ENG_INIT_OK 0
#define GLFW_INIT_ERROR 1
#define GLEW_INIT_ERROR 2
#define GLFW_CREATE_WINDOW_ERROR 3
#define ENG_UNKNOW_PLATFORM 4
#define ENG_CONTEXT_ERROR 5

#define ERRFUN 1
#define WINPOSFUN 2
#define WINSIZEFUN 3
#define WINCLOSEFUN 4
#define WINREFRESHFUN 5
#define WINFOCUSFUN 6
#define WINICONIFYFUN 7
#define MOUSEBTNFUN 8
#define CURSORPOSFUN 9
#define CURSORCNTRFUN 10
#define SCROLLFUN 11
#define KEYFUN 12
#define CHARFUN 13
#define MONITORFUN 14
#define CLCONTEXTFUN 15

typedef void (*ENG_CL_CALLBACK)(const char *, const void *, size_t, void *);

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
    void setCallback(unsigned int num, void *func, void *data = nullptr);
    std::vector<std::string> getLog();
    std::vector<std::string> getErrLog();
    void setHint (std::initializer_list<int>);
    void destroy();
private:
    int errFunc (int,const char*);
	bool GLInit;
	bool CLInit;
	GLFWvidmode* vidmode;
	GLFWmonitor* monitor;
	GLFWwindow* window;
    Log log;
    Log errlog;
	cl_uint numPlatforms;
	std::vector<EngPlatform> platforms;
    cl_platform_id* pltmp;
    ENG_CL_CALLBACK contextfunc;
	void* usr_data;
    std::initializer_list<int> hints;
};
#endif
