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
#ifdef ENG_USE_CL
typedef void (*ENG_CL_CALLBACK)(const char *, const void *, size_t, void *);

struct EngCLPlatform {

  cl_platform_id *parent_platform;
  cl_device_id *devices;
  cl_uint numDevices;
  cl_context context;
};
#endif

/**
 * @brief
 *
 */
struct EngGLPlatform {
  int width; /**< TODO */
  int height; /**< TODO */
  GLFWwindow *controll_window; /**< TODO */
  GLFWvidmode *vidmode; /**< TODO */
  GLFWmonitor *monitor; /**< TODO */
};

/**
 * @brief
 *
 */
class EngInit {
public:
  /**
   * @brief
   *
   */
  EngInit();
  /**
   * @brief
   *
   * @param title
   * @param param1
   * @param param2
   * @return unsigned int
   */
  unsigned int createGLWindow(const char *title, unsigned int param1 = 0,
                              unsigned int param2 = 0);
  /**
   * @brief
   *
   * @param title
   * @param int
   * @param param1
   * @param param2
   * @return unsigned int
   */
  unsigned int createSharedGLWindow(const char *title, unsigned int,
                                    unsigned int param1 = 0,
                                    unsigned int param2 = 0);
  /**
   * @brief
   *
   * @param int
   * @return EngGLPlatform
   */
  EngGLPlatform *getEngGLPlatform(unsigned int);
  /**
   * @brief
   *
   * @param int
   */
  void setCurrentMonitor(unsigned int);
  /**
   * @brief
   *
   */
  void cleanThreadFromMonitors();
#ifdef ENG_USE_CL
  void setCallback(unsigned int num, void *func, void *data = nullptr,
                   unsigned int numwindow = 0);
#else
  /**
   * @brief
   *
   * @param num
   * @param func
   * @param numwindow
   */
  void setCallback(unsigned int num, void *func, unsigned int numwindow = 0);
#endif
  /**
   * @brief
   *
   * @return std::vector<std::string>
   */
  std::vector<std::string> getLog();
  /**
   * @brief
   *
   * @return std::vector<std::string>
   */
  std::vector<std::string> getErrLog();
  /**
   * @brief
   *
   * @param std::initializer_list<int>
   */
  void setHint(std::initializer_list<int>);
  /**
   * @brief
   *
   * @param int
   */
  void destroyGLWindow(unsigned int);
  /**
   * @brief
   *
   */
  void clearALL();
#ifdef ENG_USE_CL
  unsigned int initCL();
  void clearCL();
  EngCLPlatform *getEngCLPlatform(unsigned int);
#endif
  /**
   * @brief
   *
   */
  ~EngInit();

private:
  bool GLInit; /**< TODO */
  Log log; /**< TODO */
  Log errlog; /**< TODO */
  std::initializer_list<int> hints; /**< TODO */
  std::vector<EngGLPlatform> glplatforms; /**< TODO */
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
