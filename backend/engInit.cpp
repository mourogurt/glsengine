#include "engInit.hpp"

void EngInit::setCallback(unsigned int num, void *func, void *data)
{
    switch (num)
    {
    case 1:
        glfwSetErrorCallback((GLFWerrorfun)func);
        break;
    case 2:
        glfwSetWindowPosCallback(render_window,(GLFWwindowposfun)func);
        break;
    case 3:
        glfwSetWindowSizeCallback(render_window,(GLFWwindowsizefun)func);
        break;
    case 4:
        glfwSetWindowCloseCallback(render_window,(GLFWwindowclosefun)func);
        break;
    case 5:
        glfwSetWindowRefreshCallback(render_window,(GLFWwindowrefreshfun)func);
        break;
    case 6:
        glfwSetWindowFocusCallback(render_window,(GLFWwindowfocusfun)func);
        break;
    case 7:
        glfwSetWindowIconifyCallback(render_window,(GLFWwindowiconifyfun)func);
        break;
    case 8:
        glfwSetMouseButtonCallback(render_window,(GLFWmousebuttonfun)func);
        break;
    case 9:
        glfwSetCursorPosCallback(render_window,(GLFWcursorposfun)func);
        break;
    case 10:
        glfwSetCursorEnterCallback(render_window,(GLFWcursorenterfun)func);
        break;
    case 11:
        glfwSetScrollCallback(render_window,(GLFWscrollfun)func);
        break;
    case 12:
        glfwSetKeyCallback(render_window,(GLFWkeyfun)func);
        break;
    case 13:
        glfwSetCharCallback(render_window,(GLFWcharfun)func);
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
	vidmode = nullptr;
	monitor = nullptr;
    render_window = nullptr;
	numPlatforms = 0;
	platforms.clear();
    contextfunc = nullptr;
    current_locker.init(1,0);
    log.writeLog(std::string("EngInit() OK"));
}

int EngInit::init(const char* title, int width, int height)
{
	cl_int err;
    err=errFunc(clGetPlatformIDs(0, NULL, &numPlatforms),"clGetPlatformIDs error: ");
	if (err!=CL_SUCCESS) return err;
	if (numPlatforms==0)
	{
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(std::string("No platform found"));
		return err;
	}
	pltmp = new cl_platform_id[numPlatforms];
	clGetPlatformIDs(numPlatforms, pltmp, NULL);
	for (cl_uint i = 0; i<numPlatforms; i++)
	{
		EngPlatform tmp;
		tmp.parent_platform = &pltmp[i];
		tmp.context=0;
        err=errFunc( clGetDeviceIDs(*(tmp.parent_platform ), CL_DEVICE_TYPE_ALL, 0, NULL, &(tmp.numDevices)),"clGetDeviceIDs error: ");
		if (err!=CL_SUCCESS)
		{
			delete [] pltmp;
			return err;
		}
		tmp.devices = new cl_device_id[tmp.numDevices];
        err = clGetDeviceIDs(*(tmp.parent_platform) , CL_DEVICE_TYPE_ALL, tmp.numDevices, tmp.devices, NULL);
        errFunc(err,"clCreateContext error: ");
		if (err!=CL_SUCCESS)
		{
			delete [] pltmp;
			delete [] tmp.devices;
			return err;
		}
        platforms.push_back(tmp);
	}
    CLInit = true;
	if (!glfwInit())
	{
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(std::string("glfwInit error"));
		return GLFW_INIT_ERROR;
	}
    if (hints.size() > 0)
        for (auto p=hints.begin(); p!=hints.end(); p+=2)
            glfwWindowHint(*p,*(p+1));
    else
        glfwDefaultWindowHints();
	monitor = glfwGetPrimaryMonitor();
	vidmode = (GLFWvidmode*)glfwGetVideoMode (monitor);
    if (render_window != nullptr)
	{
        log.writeLog("Add errlog");
        errlog.writeLog(std::string("GLFWwindow already created"));
        return GLFW_CREATE_WINDOW_ERROR;
	}
	glewExperimental=true;
    int ht,wt;
    glfwWindowHint( GLFW_VISIBLE, GL_FALSE );
    controll_window = glfwCreateWindow( 1, 1, "Thread window", NULL, NULL );
    glfwWindowHint( GLFW_VISIBLE, GL_TRUE );
	if ((height!= 0) && (width != 0))
    {
         render_window = glfwCreateWindow(width, height, title, NULL, controll_window);
        wt = width;
        ht = height;
    }
	else
    {
        render_window = glfwCreateWindow(vidmode->width, vidmode->height, title, monitor, controll_window);
        wt = vidmode->width;
        ht = vidmode->height;
    }
	for (auto p = platforms.begin(); p<platforms.end(); p++)
    {
        (*p).render_window = render_window;
        (*p).controll_window = controll_window;
        (*p).height = ht;
        (*p).width = wt;
    }
    current_locker.lock(controll_window);
    GLenum GlewInitResult = glewInit();
	if (GLEW_OK!=GlewInitResult)
	{
        log.writeLog(std::string("Add errlog"));
        errlog.writeLog(std::string(((const char*)glewGetErrorString(GlewInitResult))));
        glfwDestroyWindow(render_window);
        glfwDestroyWindow(controll_window);
		return GLEW_INIT_ERROR;
    }
    GLInit = true;
    log.writeLog(std::string("Init(const char*,int,int) OK"));
	return ENG_INIT_OK;
}

void EngInit::destroy()
{
	if (CLInit == true)
	{
		for (auto p = platforms.begin(); p<platforms.end(); p++)
		{
			if ((*p).context!=0)
				clReleaseContext((*p).context);
				delete [] (*p).devices;
		}
		delete [] pltmp;
		CLInit = false;
	}
	if (GLInit == true)
	{
        if (render_window!=NULL)
        {
            current_locker.unlock();
            glfwDestroyWindow(render_window);
        }
        if (controll_window!=NULL)
        {
            current_locker.unlock();
            glfwDestroyWindow(controll_window);
        }
		glfwTerminate();
		GLInit = false;
	}
}

cl_uint EngInit::getNumPlatforms()
{
	return numPlatforms;
}

cl_int EngInit::createContext(int num)
{

    #ifdef __linux__
		cl_context_properties properties[] = { 
			CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext(),
			CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay(), 
			CL_CONTEXT_PLATFORM, (cl_context_properties) *(platforms[num].parent_platform), 
		0};
	#elif defined _WIN32
		cl_context_properties properties[] = {
			CL_GL_CONTEXT_KHR, (cl_context_properties) wglGetCurrentContext(), 
			CL_WGL_HDC_KHR, (cl_context_properties) wglGetCurrentDC(), 
			CL_CONTEXT_PLATFORM, (cl_context_properties) *(platforms[num].parent_platform), 
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
		return ENG_UNKNOW_PLATFORM;
    #endif
	cl_int err;
    platforms[num].context = clCreateContext(properties,platforms[num].numDevices,platforms[num].devices,contextfunc,usr_data,&err);
    errFunc(err,"clCreateContext error: ");
	if (err!=CL_SUCCESS)
	{
		return err;
	}
    log.writeLog(std::string("CreateContext(int) OK"));
	return 0;
}

EngPlatform* EngInit::getEngPlatform(int num)
{
	return &(platforms.at(num));
}

ContextMutex* EngInit::getLocker()
{
    return &current_locker;
}

int EngInit::destroyContext(int num)
{
	if (platforms.at(num).context != 0)
	{
		cl_int err;
        err = clReleaseContext(platforms.at(num).context);
		platforms.at(num).context = 0;
		return err;
	}
	else
	{
        errFunc(ENG_CONTEXT_ERROR,"clReleaseContext error: ");
		return ENG_CONTEXT_ERROR;
	}
}
