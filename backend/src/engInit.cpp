#include "engInit.hpp"

bool EngInit::GLInit = false;
unsigned EngInit::numwindows = 0;
Log EngInit::log;
Log EngInit::errlog;
std::initializer_list<int> EngInit::hints;
std::vector<std::shared_ptr<EngGLPlatform>> EngInit::glplatforms;
std::queue<unsigned> EngInit::to_delete;

void EngInit::setCallback(unsigned int num, void *func, unsigned int numwindow)
{
  switch (num) {
  case 1:
    glfwSetErrorCallback((GLFWerrorfun)func);
    break;
  case 2:
    glfwSetWindowPosCallback(EngInit::glplatforms[numwindow]->controll_window,
                             (GLFWwindowposfun)func);
    break;
  case 3:
    glfwSetWindowSizeCallback(EngInit::glplatforms[numwindow]->controll_window,
                              (GLFWwindowsizefun)func);
    break;
  case 4:
    glfwSetWindowCloseCallback(glplatforms[numwindow]->controll_window,
                               (GLFWwindowclosefun)func);
    break;
  case 5:
    glfwSetWindowRefreshCallback(glplatforms[numwindow]->controll_window,
                                 (GLFWwindowrefreshfun)func);
    break;
  case 6:
    glfwSetWindowFocusCallback(glplatforms[numwindow]->controll_window,
                               (GLFWwindowfocusfun)func);
    break;
  case 7:
    glfwSetWindowIconifyCallback(glplatforms[numwindow]->controll_window,
                                 (GLFWwindowiconifyfun)func);
    break;
  case 8:
    glfwSetMouseButtonCallback(glplatforms[numwindow]->controll_window,
                               (GLFWmousebuttonfun)func);
    break;
  case 9:
    glfwSetCursorPosCallback(glplatforms[numwindow]->controll_window,
                             (GLFWcursorposfun)func);
    break;
  case 10:
    glfwSetCursorEnterCallback(glplatforms[numwindow]->controll_window,
                               (GLFWcursorenterfun)func);
    break;
  case 11:
    glfwSetScrollCallback(glplatforms[numwindow]->controll_window,
                          (GLFWscrollfun)func);
    break;
  case 12:
    glfwSetKeyCallback(glplatforms[numwindow]->controll_window,
                       (GLFWkeyfun)func);
    break;
  case 13:
    glfwSetCharCallback(glplatforms[numwindow]->controll_window,
                        (GLFWcharfun)func);
    break;
  case 14:
    glfwSetMonitorCallback((GLFWmonitorfun)func);
    break;
  default:
    dlog("Add errlog");
    errlog.writeLog(std::string("Unsuported value"));
    return;
  }
  dlog("setCallback(unsigned int,void*,void*,unsigned int) OK");
}

std::vector<std::string> EngInit::getLog() { return log.getLog(); }

std::vector<std::string> EngInit::getErrLog() { return errlog.getLog(); }

void EngInit::setHint(std::initializer_list<int> args) { hints = args; }

unsigned int EngInit::createGLWindow(const char *title, unsigned int param1,
                                     unsigned int param2) {
  if (!GLInit)
    if (!glfwInit()) {
      dlog("Add errlog");
      errlog.writeLog(std::string("glfwInit error"));
      return 0;
    }
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MIN_GL_MAJOR_VERSION);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MIN_GL_MINOR_VERSION);
  for (auto p = hints.begin(); p != hints.end(); p += 2)
    glfwWindowHint(*p, *(p + 1));
  std::shared_ptr<EngGLPlatform> gltmp = std::shared_ptr<EngGLPlatform>(new EngGLPlatform);
  int monitornum = 0;
  if (param2 == 0)
    monitornum = param1;
  int mcount;
  GLFWmonitor **monitors = glfwGetMonitors(&mcount);
  if (monitornum >= mcount) {
    dlog("Add errlog");
    errlog.writeLog(std::string("Nonexistent monitor number"));
    return 0;
  }
  gltmp->monitor = monitors[monitornum];
  gltmp->vidmode = (GLFWvidmode *)glfwGetVideoMode(gltmp->monitor);
  if ((param1 != 0) && (param2 != 0)) {
    gltmp->controll_window = glfwCreateWindow(param1, param2, title, NULL, NULL);
    gltmp->width = param1;
    gltmp->height = param2;
  } else {
    gltmp->controll_window =
        glfwCreateWindow(gltmp->vidmode->width, gltmp->vidmode->height, title,
                         gltmp->monitor, NULL);
    gltmp->width = gltmp->vidmode->width;
    gltmp->height = gltmp->vidmode->height;
  }
  if (!GLInit) {
    glfwMakeContextCurrent(gltmp->controll_window);
    glbinding::Binding::initialize(false);
    GLInit = true;
  }
  if (to_delete.size() == 0)
  {
    glplatforms.push_back(std::move(gltmp));
    numwindows++;
    dlog("createGLWindow(const char*,unsigned int,unsigned int,unsigned int) OK");
    return glplatforms.size() - 1;
  } else
  {
    unsigned number = to_delete.front();
    to_delete.pop();
    glplatforms[number] = std::move(gltmp);
    numwindows++;
    dlog("createGLWindow(const char*,unsigned int,unsigned int,unsigned int) OK");
    return number;
  }

}

unsigned int EngInit::createSharedGLWindow(const char *title,
                                           unsigned int numshare,
                                           unsigned int param1,
                                           unsigned int param2)
{
  if ((glplatforms.size() <= numshare) || (glplatforms[numshare] == NULL)) {
#ifdef _DEBUG
    log.writeLog(std::string("Add errlog"));
#endif
    errlog.writeLog(std::string("Nonexistent window number"));
    return 0;
  }
  if (hints.size() > 0)
    for (auto p = hints.begin(); p != hints.end(); p += 2)
      glfwWindowHint(*p, *(p + 1));
  else
    glfwDefaultWindowHints();
  std::shared_ptr<EngGLPlatform> gltmp = std::shared_ptr<EngGLPlatform>(new EngGLPlatform);
  int monitornum = 0;
  if (param2 == 0)
    monitornum = param1;
  int mcount;
  GLFWmonitor **monitors = glfwGetMonitors(&mcount);
  if (monitornum >= mcount) {
    dlog("Add errlog");
    errlog.writeLog(std::string("Nonexistent monitor number"));
    return 0;
  }
  gltmp->monitor = monitors[monitornum];
  gltmp->vidmode = (GLFWvidmode *)glfwGetVideoMode(gltmp->monitor);
  if ((param1 != 0) && (param2 != 0)) {
    gltmp->controll_window = glfwCreateWindow(
        param1, param2, title, NULL, glplatforms[numshare]->controll_window);
    gltmp->width = param1;
    gltmp->height = param2;
  } else {
    gltmp->controll_window =
        glfwCreateWindow(gltmp->vidmode->width, gltmp->vidmode->height, title,
                         gltmp->monitor, glplatforms[numshare]->controll_window);
    gltmp->width = gltmp->vidmode->width;
    gltmp->height = gltmp->vidmode->height;
  }
  if (to_delete.size() == 0)
  {
    glplatforms.push_back(std::move(gltmp));
    numwindows++;
    dlog("createSharedGLWindow(const char*,unsigned "
                               "int,unsigned int,unsigned int,unsigned int) OK");
    return glplatforms.size() - 1;
  } else
  {
    unsigned number = to_delete.front();
    to_delete.pop();
    glplatforms[number] = std::move(gltmp);
    numwindows++;
    dlog("createSharedGLWindow(const char*,unsigned "
                               "int,unsigned int,unsigned int,unsigned int) OK");
    return number;
  }

}

std::weak_ptr<EngGLPlatform> EngInit::getEngGLPlatform(unsigned int number) {
  return glplatforms[number];
}

void EngInit::clearALL() {
  unsigned int i = glplatforms.size() - 1;
  while (glplatforms.size() > 0) {
    destroyGLWindow(i);
    i--;
  }
}

void EngInit::setCurrentMonitor(unsigned int numwindow) {
  if ((numwindow >= glplatforms.size()) || (glplatforms[numwindow] == NULL)) {
    dlog("Add errlog");
    errlog.writeLog(std::string("Nonexistent window number"));
    return;
  }
  glfwMakeContextCurrent(NULL);
  glfwMakeContextCurrent(glplatforms[numwindow]->controll_window);
  dlog("setCurrentMonitor(unsigned int) OK");
}

void EngInit::cleanThreadFromMonitors() { glfwMakeContextCurrent(NULL); }

void EngInit::destroyGLWindow(unsigned int numwindow) {
  if (GLInit) {
    if ((numwindow >= glplatforms.size()) || (glplatforms[numwindow] == NULL)) {
      dlog("Add errlog");
      errlog.writeLog(std::string("Nonexistent window number"));
      return;
    }
    if (glplatforms[numwindow]->controll_window != NULL) {
      glfwDestroyWindow(glplatforms[numwindow]->controll_window);
      glplatforms[numwindow]->controll_window = NULL;
      to_delete.push(numwindow);
      numwindows--;
      if (numwindows == 0) {
        glplatforms.clear();
        to_delete = std::queue<unsigned>();
        glfwTerminate();
        GLInit = false;
      }
    }
  }
  dlog("destroyGLWindow(unsigned int) OK");
}
