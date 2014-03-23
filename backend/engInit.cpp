#include "engInit.hpp"

void EngInit::setCallback(unsigned int num, void *func, void *data, unsigned int numwindow)
{
    switch (num)
    {
    case 1:
        glfwSetErrorCallback((GLFWerrorfun)func);
        break;
    case 2:
        glfwSetWindowPosCallback(glplatforms[numwindow].controll_window,(GLFWwindowposfun)func);
        break;
    case 3:
        glfwSetWindowSizeCallback(glplatforms[numwindow].controll_window,(GLFWwindowsizefun)func);
        break;
    case 4:
        glfwSetWindowCloseCallback(glplatforms[numwindow].controll_window,(GLFWwindowclosefun)func);
        break;
    case 5:
        glfwSetWindowRefreshCallback(glplatforms[numwindow].controll_window,(GLFWwindowrefreshfun)func);
        break;
    case 6:
        glfwSetWindowFocusCallback(glplatforms[numwindow].controll_window,(GLFWwindowfocusfun)func);
        break;
    case 7:
        glfwSetWindowIconifyCallback(glplatforms[numwindow].controll_window,(GLFWwindowiconifyfun)func);
        break;
    case 8:
        glfwSetMouseButtonCallback(glplatforms[numwindow].controll_window,(GLFWmousebuttonfun)func);
        break;
    case 9:
        glfwSetCursorPosCallback(glplatforms[numwindow].controll_window,(GLFWcursorposfun)func);
        break;
    case 10:
        glfwSetCursorEnterCallback(glplatforms[numwindow].controll_window,(GLFWcursorenterfun)func);
        break;
    case 11:
        glfwSetScrollCallback(glplatforms[numwindow].controll_window,(GLFWscrollfun)func);
        break;
    case 12:
        glfwSetKeyCallback(glplatforms[numwindow].controll_window,(GLFWkeyfun)func);
        break;
    case 13:
        glfwSetCharCallback(glplatforms[numwindow].controll_window,(GLFWcharfun)func);
        break;
    case 14:
        glfwSetMonitorCallback((GLFWmonitorfun)func);
        break;
    case 15:
        contextfunc=(ENG_CL_CALLBACK)func;
        usr_data=data;
        break;
    default:
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(std::string("Unsuported value"));
    }
}

std::vector<std::string> EngInit::getLog()
{
    return log.getLog();
}

std::vector<std::string> EngInit::getErrLog()
{
    return errlog.getLog();
}

int EngInit::errFunc(int err,const char* str)
{
	if (err!=CL_SUCCESS)
	{
		std::stringstream tmp;
		tmp<<str<<err;
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(tmp.str());
	}
	return err;
}

void EngInit::setHint(std::initializer_list<int> args)
{
    hints = args;
}

EngInit::EngInit()
{
	GLInit = false;
	CLInit = false;
	numPlatforms = 0;
    glplatforms.clear();
    clplatforms.clear();
    contextfunc = nullptr;
    log.writeLog(std::string("EngInit() OK"));
}

unsigned int EngInit::initCL()
{
    if (!CLInit)
    {
        cl_int err;
        cl_uint numPlatforms;
        err=errFunc(clGetPlatformIDs(0, NULL, &numPlatforms),"clGetPlatformIDs error: ");
        if (err!=CL_SUCCESS) return err;
        if (numPlatforms==0)
        {
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string("No platform found"));
            return 0;
        }
        pltmp = new cl_platform_id[numPlatforms];
        clGetPlatformIDs(numPlatforms, pltmp, NULL);
        for (cl_uint i = 0; i<numPlatforms; i++)
        {
            EngCLPlatform tmp;
            tmp.parent_platform = &pltmp[i];
            tmp.context=0;
            err=errFunc( clGetDeviceIDs(*(tmp.parent_platform ), CL_DEVICE_TYPE_ALL, 0, NULL, &(tmp.numDevices)),"clGetDeviceIDs error: ");
            if (err!=CL_SUCCESS)
            {
                delete [] pltmp;
                return 0;
            }
            tmp.devices = new cl_device_id[tmp.numDevices];
            err = clGetDeviceIDs(*(tmp.parent_platform) , CL_DEVICE_TYPE_ALL, tmp.numDevices, tmp.devices, NULL);
            errFunc(err,"clCreateContext error: ");
            if (err!=CL_SUCCESS)
            {
                delete [] pltmp;
                delete [] tmp.devices;
                return 0;
            }
            #ifdef __linux__
                cl_context_properties properties[] = {
                    CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext(),
                    CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay(),
                    CL_CONTEXT_PLATFORM, (cl_context_properties) *(tmp.parent_platform),
                0};
            #elif defined _WIN32
                cl_context_properties properties[] = {
                    CL_GL_CONTEXT_KHR, (cl_context_properties) wglGetCurrentContext(),
                    CL_WGL_HDC_KHR, (cl_context_properties) wglGetCurrentDC(),
                    CL_CONTEXT_PLATFORM, (cl_context_properties) *(tmp.parent_platform),
                0};
            #elif defined TARGET_OS_MAC
                CGLContextObj glContext = CGLGetCurrentContext();
                CGLShareGroupObj shareGroup = CGLGetShareGroup(glContext);
                cl_context_properties properties[] = {
                    CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
                    (cl_context_properties)shareGroup,
                0};
            #else
                log.writeLog(std::string("Add errlog"));
                errlog.writeLog(std::string("Unsupported platform"));
                return 0;
            #endif
            tmp.context = clCreateContext(properties,tmp.numDevices,tmp.devices,contextfunc,usr_data,&err);
            errFunc(err,"clCreateContext error: ");
            if (err!=CL_SUCCESS)
            {
                delete [] pltmp;
                delete [] tmp.devices;
                return 0;
            }
            clplatforms.push_back(tmp);
        }
        CLInit = true;
        log.writeLog(std::string("initCL() OK"));
        return clplatforms.size() - 1;
    }
    else
    {
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(std::string("OpenCL already initialized"));
        return 0;
    }
}

unsigned int EngInit::createGLWindow(const char* title,unsigned int param1,unsigned int param2)
{
    if (!GLInit)
        if (!glfwInit())
        {
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string("glfwInit error"));
            return 0;
        }
    if (hints.size() > 0)
        for (auto p=hints.begin(); p!=hints.end(); p+=2)
            glfwWindowHint(*p,*(p+1));
    else
        glfwDefaultWindowHints();
    EngGLPlatform gltmp;
    int monitornum = 0;
    if (param2 == 0)
        monitornum = param1;
    int mcount;
    GLFWmonitor** monitors = glfwGetMonitors(&mcount);
    if (monitornum >= mcount)
    {
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(std::string("Nonexistent monitor number"));
        return 0;
    }
    gltmp.monitor = monitors[monitornum];
    gltmp.vidmode = (GLFWvidmode*)glfwGetVideoMode (gltmp.monitor);
    if ((param1!= 0) && (param2 != 0))
    {
        gltmp.controll_window = glfwCreateWindow(param1, param2, title, NULL, NULL);
        gltmp.width = param1;
        gltmp.height = param2;
    }
    else
    {
        gltmp.controll_window = glfwCreateWindow(gltmp.vidmode->width, gltmp.vidmode->height, title, gltmp.monitor, NULL);
        gltmp.width = gltmp.vidmode->width;
        gltmp.height = gltmp.vidmode->height;
    }
    glplatforms.push_back(gltmp);
    if (!GLInit)
    {
        glfwMakeContextCurrent(gltmp.controll_window);
        glewExperimental=true;
        GLenum GlewInitResult = glewInit();
        if (GLEW_OK!=GlewInitResult)
        {
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string(((const char*)glewGetErrorString(GlewInitResult))));
            glfwDestroyWindow(gltmp.controll_window);
            return 0;
        }
        GLInit = true;
    }
    log.writeLog(std::string("createGLWindow(const char*,unsigned int,unsigned int,unsigned int) OK"));
    return glplatforms.size() - 1;
}

EngGLPlatform* EngInit::getEngGLPlatform (unsigned int number)
{
    return &glplatforms[number];
}

EngCLPlatform* EngInit::getEngCLPlatform (unsigned int number)
{
    return &clplatforms[number];
}

void EngInit::clearCL()
{
    if (CLInit)
    {
        for (auto p = clplatforms.begin(); p<clplatforms.end(); p++)
        {
            if ((*p).context!=0)
                clReleaseContext((*p).context);
                delete [] (*p).devices;
        }
        delete [] pltmp;
        CLInit = false;
    }
}

void EngInit::destroyGLWindow(unsigned int numwindow)
{
    if (GLInit)
    {
        if (numwindow >= glplatforms.size())
        {
            log.writeLog(std::string("Add errlog"));
            errlog.writeLog(std::string("Nonexistent window number"));
            return;
        }
        if (glplatforms[numwindow].controll_window != NULL)
        {
            glfwDestroyWindow(glplatforms[numwindow].controll_window);
            glplatforms.erase(glplatforms.begin() + numwindow);
            if (glplatforms.size() == 0)
            {
                glfwTerminate();
                GLInit = false;
            }
        }
    }
}

void EngInit::clearALL()
{
    clearCL();
    for (unsigned int i = 0; i < glplatforms.size(); i++)
        destroyGLWindow(i);
}

void EngInit::setCurrentMonitor(unsigned int numwindow)
{
    if (numwindow >= glplatforms.size())
    {
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(std::string("Nonexistent window number"));
        return;
    }
    glfwMakeContextCurrent(NULL);
    glfwMakeContextCurrent(glplatforms[numwindow].controll_window);
}
