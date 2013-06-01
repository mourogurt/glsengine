#include "engInit.hpp" 

std::vector<const char*> EngLog::GetLog()
{
	return log;
}

void EngLog::WriteLog(const char* buff)
{
	log.push_back(buff);
}

void EngLog::ClearLog()
{
	log.clear();
}

EngLog::~EngLog()
{
	ClearLog();
}

void EngInit::SetCallback(EngErrFunct callback)
{
	glfwSetErrorCallback(callback.func);
}

void EngInit::SetCallback (EngWinPosFunct callback)
{
	glfwSetWindowPosCallback(window,callback.func);
}

void EngInit::SetCallback (EngWinSizeFunct callback)
{
	glfwSetWindowSizeCallback(window,callback.func);
}

void EngInit::SetCallback (EngWinCloseFunct callback)
{
	glfwSetWindowCloseCallback(window,callback.func);
}

void EngInit::SetCallback (EngWinRefFunct callback)
{
	glfwSetWindowRefreshCallback(window,callback.func);
}
void EngInit::SetCallback (EngWinFocFunct callback)
{
	glfwSetWindowFocusCallback(window,callback.func);
}

void EngInit::SetCallback (EngWinIconFunct callback)
{
	glfwSetWindowIconifyCallback(window,callback.func);
}

void EngInit::SetCallback (EngMouseButFunct callback)
{
	glfwSetMouseButtonCallback(window,callback.func);
}

void EngInit::SetCallback (EngCurPosFunct callback)
{
	glfwSetCursorPosCallback(window,callback.func);
}

void EngInit::SetCallback (EngCurEnterFunct callback)
{
	glfwSetCursorEnterCallback(window,callback.func);
}

void EngInit::SetCallback (EngScrollFunct callback)
{
	glfwSetScrollCallback(window,callback.func);
}

void EngInit::SetCallback (EngKeyFunct callback)
{
	glfwSetKeyCallback(window,callback.func);
}

void EngInit::SetCallback (EngCharFunct callback)
{
	glfwSetCharCallback(window,callback.func);
}

void EngInit::SetCallback (EngMonitorFunct callback)
{
	glfwSetMonitorCallback(callback.func);
}

void EngInit::SetCallback(EngContextFunct functin, void* data)
{
	funct=functin;
	usr_data=data;
}

std::vector<const char*> EngInit::GetLog()
{
	return log.GetLog();
}

std::vector<const char*> EngInit::GetErrLog()
{
	return errlog.GetLog();
}

void EngInit::ClearLog()
{
	log.ClearLog();
}

void EngInit::ClearErrLog()
{
	errlog.ClearLog();
}

int EngInit::ErrFunc(int err,const char* str)
{
	if (err!=CL_SUCCESS)
	{
		std::stringstream tmp;
		tmp<<str<<err;
		log.WriteLog("Add errlog");
		errlog.WriteLog(tmp.str().c_str());
	}
	return err;
}

void EngInit::SetHint(std::initializer_list<int> args)
{
	for (auto p=args.begin(); p!=args.end(); p+=2) 
		glfwWindowHint(*p,*(p+1));
}

void EngInit::SetHint()
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
	log.ClearLog();
	errlog.ClearLog();
	numPlatforms = 0;
	platforms.clear();
	funct.func = nullptr;
	log.WriteLog("EngInit() OK");
}

int EngInit::Init(const char* title, int width, int height)
{
	cl_int err;
	err=ErrFunc(clGetPlatformIDs(0, NULL, &numPlatforms),"clGetPlatformIDs error: ");
	if (err!=CL_SUCCESS) return err;
	if (numPlatforms==0)
	{
		log.WriteLog("Add errlog");
		errlog.WriteLog("No platform found");
		return err;
	}
	pltmp = new cl_platform_id[numPlatforms];
	clGetPlatformIDs(numPlatforms, pltmp, NULL);
	for (cl_uint i = 0; i<numPlatforms; i++)
	{
		EngPlatform tmp;
		tmp.parent_platform = &pltmp[i];
		tmp.context=0;
		err=ErrFunc( clGetDeviceIDs(*(tmp.parent_platform ), CL_DEVICE_TYPE_ALL, 0, NULL, &(tmp.numDevices)),"clGetDeviceIDs error: ");
		if (err!=CL_SUCCESS)
		{
			delete [] pltmp;
			return err;
		}
		tmp.devices = new cl_device_id[tmp.numDevices];
		clGetDeviceIDs(*(tmp.parent_platform) , CL_DEVICE_TYPE_ALL, tmp.numDevices, tmp.devices, NULL);
		ErrFunc(err,"clCreateContext error: ");
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
		log.WriteLog("Add errlog");
		errlog.WriteLog("glfwInit error");
		return GLFW_INIT_ERROR;
	}
	monitor = glfwGetPrimaryMonitor();
	vidmode = (GLFWvidmode*)glfwGetVideoMode (monitor);
	if (window != nullptr)
	{
		log.WriteLog("Add errlog");
		errlog.WriteLog("GLFWwindow already created");
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
		log.WriteLog("Add errlog");
		errlog.WriteLog((const char*)glewGetErrorString(GlewInitResult));
		glfwDestroyWindow(window);
		return GLEW_INIT_ERROR;
	}
	log.WriteLog("Init(const char*,int,int) OK");
	return ENG_INIT_OK;
	GLInit = true;
}

void EngInit::Destroy()
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
	log.ClearLog();
	errlog.ClearLog();
}

cl_uint EngInit::GetNumPlatforms()
{
	return numPlatforms;
}

cl_int EngInit::CreateContext(int num)
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
		log.WriteLog("Add errlog");
		errlog.WriteLog("Unsupported platform");
		return ENG_UNKNOW_PLATFORM;
	#endif
	cl_int err;
	platforms[num].context = clCreateContext(properties,platforms[num].numDevices,platforms[num].devices,funct.func,usr_data,&err);
	ErrFunc(err,"clCreateContext error: ");
	if (err!=CL_SUCCESS)
	{
		return err;
	}
	log.WriteLog("CreateContext(int) OK");
	return 0;
}

EngPlatform* EngInit::GetEngPlatform(int num)
{
	return &(platforms.at(num));
}

int EngInit::DestroyContext(int num)
{
	if (platforms.at(num).context != 0)
		clReleaseContext(platforms.at(num).context);
	else
	{
		ErrFunc(ENG_CONTEXT_ERROR,"clReleaseContext error: ");
		return ENG_CONTEXT_ERROR;
	}
}