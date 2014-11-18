#ifndef ENGINIT_HPP
#define ENGINIT_HPP
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#define GLFW_USE_EGL
#include <GLFW/glfw3.h>
#include <log.hpp>
#ifdef ENG_USE_CL
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <sstream>
#endif

#define MIN_GL_MAJOR_VERSION 3
#define MIN_GL_MINOR_VERSION 2

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

#ifdef _DEBUG
#define dlog(n) log.writeLog(n);
#else
#define dlog(n)
#endif
//TODO: Add loader of functions
#ifdef ENG_USE_CL
typedef void (*ENG_CL_CALLBACK)(const char *, const void *, size_t, void *);

struct EngCLPlatform {

  cl_platform_id *parent_platform;
  cl_device_id *devices;
  cl_uint numDevices;
  cl_context context;
};
#endif

struct EngGLPlatform {
  int width;
  int height;
  GLFWwindow *controll_window;
  GLFWvidmode *vidmode;
  GLFWmonitor *monitor;
};

class EngInit {
public:
  EngInit();
  unsigned int createGLWindow(const char *title, unsigned int param1 = 0,
                              unsigned int param2 = 0);
  unsigned int createSharedGLWindow(const char *title, unsigned int,
                                    unsigned int param1 = 0,
                                    unsigned int param2 = 0);
  EngGLPlatform *getEngGLPlatform(unsigned int);
  void setCurrentMonitor(unsigned int);
  void cleanThreadFromMonitors();
#ifdef ENG_USE_CL
  void setCallback(unsigned int num, void *func, void *data = nullptr,
                   unsigned int numwindow = 0);
#else
  void setCallback(unsigned int num, void *func, unsigned int numwindow = 0);
#endif
  std::vector<std::string> getLog();
  std::vector<std::string> getErrLog();
  void setHint(std::initializer_list<int>);
  void destroyGLWindow(unsigned int);
  void clearALL();
#ifdef ENG_USE_CL
  unsigned int initCL();
  void clearCL();
  EngCLPlatform *getEngCLPlatform(unsigned int);
#endif
  ~EngInit();

private:
  bool GLInit;
  Log log;
  Log errlog;
  std::initializer_list<int> hints;
  std::vector<EngGLPlatform> glplatforms;
#ifdef ENG_USE_CL
  int errFunc(int, const char *);
  bool CLInit;
  cl_uint numPlatforms;
  std::vector<EngCLPlatform> clplatforms;
  cl_platform_id *pltmp;
  ENG_CL_CALLBACK contextfunc;
  void *usr_data;
#endif
};
#endif
