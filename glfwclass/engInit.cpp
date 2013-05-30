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
	log.clear();
}

EngLog::~EngLog()
{
	ClearLog();
}

InitGLClass::InitGLClass()
{
	Init=false;
	window=nullptr;
	if (!glfwInit())
	{
		log.WriteLog("Add errlog");
		errlog.WriteLog("glfwInit error");
		Init=false;
	}
	monitor = glfwGetPrimaryMonitor();
	vidmode = (GLFWvidmode*)glfwGetVideoMode (monitor);
	Init=true;
	log.WriteLog("InitGLClass() OK");
}

std::vector<const char*> InitGLClass::GetLog()
{
	return log.GetLog();
}

std::vector<const char*> InitGLClass::GetErrLog()
{
	return errlog.GetLog();
}

int InitGLClass::InitGL(const char* title, int width, int height)
{
	if (Init==false)
		return 1;
	if (window !=nullptr)
	{
		log.WriteLog("Add errlog");
		errlog.WriteLog("GLFWwindow already created");
	}
	glewExperimental=true;
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window);
	GLenum GlewInitResult = glewInit();
	if (GLEW_OK!=GlewInitResult)
	{
		log.WriteLog("Add errlog");
		errlog.WriteLog((const char*)glewGetErrorString(GlewInitResult));
		DestroyGL();
		return GLEW_INIT_ERROR;
	}
	log.WriteLog("InitGL(const char*, int, int) OK");
	return ENG_INIT_OK;
}



int InitGLClass::InitGL(const char* title)
{
	if (Init==false)
		return GLFW_INIT_ERROR;
	glewExperimental=true;
	window = glfwCreateWindow(vidmode->width, vidmode->height, title, monitor, NULL);
	glfwMakeContextCurrent(window);
	GLenum GlewInitResult = glewInit();
	if (GLEW_OK!=GlewInitResult)
	{
		log.WriteLog("Add errlog");
		errlog.WriteLog((const char*)glewGetErrorString(GlewInitResult));
		DestroyGL();
		return GLEW_INIT_ERROR;
	}
	log.WriteLog("InitGL(const char*) OK");
	return ENG_INIT_OK;
}

void InitGLClass::SetHint(std::initializer_list<int> args)
{
	for (auto p=args.begin(); p!=args.end(); p+=2) 
		glfwWindowHint(*p,*(p+1));
}

void InitGLClass::SetHint()
{
	glfwDefaultWindowHints();
}

GLFWwindow* InitGLClass::GetWindow()
{
	return window;
}

void InitGLClass::SetCallback(EngErrFunct callback)
{
	glfwSetErrorCallback(callback.func);
}

void InitGLClass::SetCallback (EngWinPosFunct callback)
{
	glfwSetWindowPosCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngWinSizeFunct callback)
{
	glfwSetWindowSizeCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngWinCloseFunct callback)
{
	glfwSetWindowCloseCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngWinRefFunct callback)
{
	glfwSetWindowRefreshCallback(window,callback.func);
}
void InitGLClass::SetCallback (EngWinFocFunct callback)
{
	glfwSetWindowFocusCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngWinIconFunct callback)
{
	glfwSetWindowIconifyCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngMouseButFunct callback)
{
	glfwSetMouseButtonCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngCurPosFunct callback)
{
	glfwSetCursorPosCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngCurEnterFunct callback)
{
	glfwSetCursorEnterCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngScrollFunct callback)
{
	glfwSetScrollCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngKeyFunct callback)
{
	glfwSetKeyCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngCharFunct callback)
{
	glfwSetCharCallback(window,callback.func);
}

void InitGLClass::SetCallback (EngMonitorFunct callback)
{
	glfwSetMonitorCallback(callback.func);
}

void InitGLClass::DestroyGL()
{
	if (Init==true)
	{
		if (window!=nullptr)
			glfwDestroyWindow(window);
		glfwTerminate();
	}
}

InitGLClass::~InitGLClass()
{
	if (Init==true)
	{
		if (window!=nullptr)
			glfwDestroyWindow(window);
		glfwTerminate();
	}
	log.ClearLog();
	errlog.ClearLog();
}

InitCLClass::InitCLClass()
{
	log.ClearLog();
	errlog.ClearLog();
	numContexts=0;
	numPropereties=0;
	parent = nullptr;
}

bool InitCLClass::ErrCLFunc(cl_int err,const char* str)
{
	if (err!=CL_SUCCESS)
	{
		std::stringstream tmp;
		tmp<<str<<err;
		log.WriteLog("Add errlog");
		errlog.WriteLog(tmp.str().c_str());
		return 1;
	} else return 0;
}

int InitCLClass::InitCL(InitGLClass* ingl)
{
	bool err;
	parent=ingl;
	cl_uint numPlatforms;
	err=ErrCLFunc(clGetPlatformIDs(0, NULL, &numPlatforms),"InitCL clGetPlatformIDs error: ");
	if (err==0) return 1;
	if (numPlatforms==0)
	{
		log.WriteLog("Add errlog");
		errlog.WriteLog("No platform found");
		return 1;
	}
	cl_platform_id* pltmp = new cl_platform_id[numPlatforms];
	clGetPlatformIDs(numPlatforms, pltmp, NULL);
	for (cl_uint i=0; i<numPlatforms; i++)
		platforms.push_back(pltmp[i]);
	delete [] pltmp;
	for (auto i = platforms.begin(); i<platforms.end(); i++)
	{
		cl_uint numDevices;
		err=ErrCLFunc( clGetDeviceIDs(*i, CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices),"InitCL clGetDeviceIDs error: ");
		if (err==0) return 1;
		cl_device_id* dvtmp = new cl_device_id[numDevices];
		clGetDeviceIDs(*i, CL_DEVICE_TYPE_ALL, numDevices, dvtmp, NULL);
		EngDevice edvtmp;
		edvtmp.parent_platform = &(*i);
		for (cl_uint j = 0; j<numDevices; j++)
			edvtmp.devices.push_back(dvtmp[j]);
		devices.push_back(edvtmp);
		delete [] dvtmp;
	}
	return 0;
}