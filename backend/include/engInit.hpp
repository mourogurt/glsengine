#ifndef ENGINIT_HPP
#define ENGINIT_HPP
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#define GLFW_USE_EGL
#include <GLFW/glfw3.h>
#include <log.hpp>
#include <queue>

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

struct EngGLPlatform {
  int width;
  int height;
  GLFWwindow *controll_window;
  GLFWvidmode *vidmode;
  GLFWmonitor *monitor;
};

//TODO: Add GL debug function

class EngInit {
public:
  static unsigned int createGLWindow(const char *title, unsigned int param1 = 0,
                              unsigned int param2 = 0);
  static unsigned int createSharedGLWindow(const char *title, unsigned int,
                                    unsigned int param1 = 0,
                                    unsigned int param2 = 0);
  static std::weak_ptr<EngGLPlatform> getEngGLPlatform(unsigned int);
  static void setCurrentMonitor(unsigned int);
  static void cleanThreadFromMonitors();
  static void setCallback(unsigned int num, void *func, unsigned int numwindow = 0);
  static std::vector<std::string> getLog();
  static std::vector<std::string> getErrLog();
  static void setHint(std::initializer_list<int>);
  static void destroyGLWindow(unsigned int);
  static void clearALL();

private:
  static bool GLInit;
  static Log log;
  static Log errlog;
  static std::initializer_list<int> hints;
  static std::vector<std::shared_ptr<EngGLPlatform>> glplatforms;
  static unsigned numwindows;
  static std::queue<unsigned> to_delete;
};
#endif
