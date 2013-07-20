#include "engInit.hpp" 

std::vector<const char*> EngLog::getLog()
{
    std::vector<const char*> rlog = log;
    return rlog;
}

void EngLog::writeLog(const char* buff)
{
	log.push_back(buff);
}

void EngLog::clearLog()
{
	log.clear();
}

void EngInit::setCallback(EngErrFunct callback)
{
	glfwSetErrorCallback(callback.func);
}

void EngInit::setCallback (EngWinPosFunct callback)
{
	glfwSetWindowPosCallback(window,callback.func);
}

void EngInit::setCallback (EngWinSizeFunct callback)
{
	glfwSetWindowSizeCallback(window,callback.func);
}

void EngInit::setCallback (EngWinCloseFunct callback)
{
	glfwSetWindowCloseCallback(window,callback.func);
}

void EngInit::setCallback (EngWinRefFunct callback)
{
	glfwSetWindowRefreshCallback(window,callback.func);
}
void EngInit::setCallback (EngWinFocFunct callback)
{
	glfwSetWindowFocusCallback(window,callback.func);
}

void EngInit::setCallback (EngWinIconFunct callback)
{
	glfwSetWindowIconifyCallback(window,callback.func);
}

void EngInit::setCallback (EngMouseButFunct callback)
{
	glfwSetMouseButtonCallback(window,callback.func);
}

void EngInit::setCallback (EngCurPosFunct callback)
{
	glfwSetCursorPosCallback(window,callback.func);
}

void EngInit::setCallback (EngCurEnterFunct callback)
{
	glfwSetCursorEnterCallback(window,callback.func);
}

void EngInit::setCallback (EngScrollFunct callback)
{
	glfwSetScrollCallback(window,callback.func);
}

void EngInit::setCallback (EngKeyFunct callback)
{
	glfwSetKeyCallback(window,callback.func);
}

void EngInit::setCallback (EngCharFunct callback)
{
	glfwSetCharCallback(window,callback.func);
}

void EngInit::setCallback (EngMonitorFunct callback)
{
	glfwSetMonitorCallback(callback.func);
}

void EngInit::setCallback(EngContextFunct functin, void* data)
{
	funct=functin;
	usr_data=data;
}

std::vector<const char*> EngInit::getLog()
{
    return log.getLog();
}

std::vector<const char*> EngInit::getErrLog()
{
    return errlog.getLog();
}

void EngInit::clearLog()
{
    log.clearLog();
}

void EngInit::clearErrLog()
{
    errlog.clearLog();
}

int EngInit::errFunc(int err,const char* str)
{
	if (err!=CL_SUCCESS)
	{
		std::stringstream tmp;
		tmp<<str<<err;
        log.writeLog("Add errlog");
        errlog.writeLog(tmp.str().c_str());
	}
	return err;
}

void EngInit::setHint(std::initializer_list<int> args)
{
	for (auto p=args.begin(); p!=args.end(); p+=2) 
		glfwWindowHint(*p,*(p+1));
}

void EngInit::setHint()
{
	glfwDefaultWindowHints();
}

EngInit::EngInit()
{
	GLInit = false;
	CLInit = false;
	vidmode = nullptr;
	monitor = nullptr;
	window = nullptr;
    log.clearLog();
    errlog.clearLog();
	numPlatforms = 0;
	platforms.clear();
	funct.func = nullptr;
    log.writeLog("EngInit() OK");
}

int EngInit::init(const char* title, int width, int height)
{
	cl_int err;
    err=errFunc(clGetPlatformIDs(0, NULL, &numPlatforms),"clGetPlatformIDs error: ");
	if (err!=CL_SUCCESS) return err;
	if (numPlatforms==0)
	{
        log.writeLog("Add errlog");
        errlog.writeLog("No platform found");
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
		clGetDeviceIDs(*(tmp.parent_platform) , CL_DEVICE_TYPE_ALL, tmp.numDevices, tmp.devices, NULL);
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
        log.writeLog("Add errlog");
        errlog.writeLog("glfwInit error");
		return GLFW_INIT_ERROR;
	}
	monitor = glfwGetPrimaryMonitor();
	vidmode = (GLFWvidmode*)glfwGetVideoMode (monitor);
	if (window != nullptr)
	{
        log.writeLog("Add errlog");
        errlog.writeLog("GLFWwindow already created");
		return GLFW_CREATE_WINDOW_ERROR;
	}
	glewExperimental=true;
	if ((height!= 0) && (width != 0))
		window = glfwCreateWindow(width, height, title, NULL, NULL);
	else
		window = glfwCreateWindow(vidmode->width, vidmode->height, title, monitor, NULL);
	for (auto p = platforms.begin(); p<platforms.end(); p++)
		(*p).window=window;
	glfwMakeContextCurrent(window);
	GLenum GlewInitResult = glewInit();
	if (GLEW_OK!=GlewInitResult)
	{
        log.writeLog("Add errlog");
        errlog.writeLog((const char*)glewGetErrorString(GlewInitResult));
        glfwDestroyWindow(window);
		return GLEW_INIT_ERROR;
	}
	GLInit = true;
    log.writeLog("Init(const char*,int,int) OK");
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
		if (window!=nullptr)
			glfwDestroyWindow(window);
		glfwTerminate();
		GLInit = false;
	}
    log.clearLog();
    errlog.clearLog();
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
        log.writeLog("Add errlog");
        errlog.writeLog("Unsupported platform");
		return ENG_UNKNOW_PLATFORM;
	#endif
	cl_int err;
	platforms[num].context = clCreateContext(properties,platforms[num].numDevices,platforms[num].devices,funct.func,usr_data,&err);
    errFunc(err,"clCreateContext error: ");
	if (err!=CL_SUCCESS)
	{
		return err;
	}
    log.writeLog("CreateContext(int) OK");
	return 0;
}

EngPlatform* EngInit::getEngPlatform(int num)
{
	return &(platforms.at(num));
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
