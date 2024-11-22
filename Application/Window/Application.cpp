/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "Application.hpp"
#include "Direct2D.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Application::Application()
{
}

//===========================================================================
Application::~Application()
{
}

//===========================================================================
bool Application::initialize(HINSTANCE hInstance)
{
	_hInstance = hInstance;


	//-----------------------------------------------------------------------
	if (initializeCOM() == false)
	{
		return false;
	}


	//-----------------------------------------------------------------------
	if (Direct2D::newFactory() == false)
	{
		uninitializeCOM();

		return false;
	}


	//-----------------------------------------------------------------------
	enableDebugRuntimeMemoryCheck();


	//-----------------------------------------------------------------------
	startDebugRuntimeMemoryLeackCheck();


	return true;
}

void Application::terminate(void)
{
	//-----------------------------------------------------------------------
	endDebugRuntimeMemoryLeackCheck();


	//-----------------------------------------------------------------------
	Direct2D::deleteFactory();


	//-----------------------------------------------------------------------
	uninitializeCOM();


	//-----------------------------------------------------------------------
	_hInstance = nullptr;
}

//===========================================================================
void Application::enableDebugRuntimeMemoryCheck(void)
{
	//-----------------------------------------------------------------------
#ifdef _DEBUG
	// Enable run-time memory check for debug builds.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	//-----------------------------------------------------------------------
#if 0
#ifdef _DEBUG
	char* memory_leack_p0;
	char* memory_leack_p1;
	void* memory_leack_p2;
	void* memory_leack_p3;


	memory_leack_p0 = new char[16];
	memory_leack_p1 = cpp_new char[16];
	memory_leack_p2 = malloc(16);
	memory_leack_p3 = calloc(16, 1);
#endif
#endif
}

//===========================================================================
#ifdef _DEBUG
static _CrtMemState _CrtMemState_start;
static _CrtMemState _CrtMemState_end;
static _CrtMemState _CrtMemState_diff;
#endif

//===========================================================================
void Application::startDebugRuntimeMemoryLeackCheck(void)
{
	//-----------------------------------------------------------------------
#ifdef _DEBUG
	_CrtMemCheckpoint(&_CrtMemState_start);
#endif


	//-----------------------------------------------------------------------
#if 0
#ifdef _DEBUG
	char* memory_leack_p0;
	char* memory_leack_p1;
	void* memory_leack_p2;
	void* memory_leack_p3;


	memory_leack_p0 = new char[16];
	memory_leack_p1 = cpp_new char[16];
	memory_leack_p2 = malloc(16);
	memory_leack_p3 = calloc(16, 1);
#endif
#endif
}

void Application::endDebugRuntimeMemoryLeackCheck(void)
{
#ifdef _DEBUG
	_CrtMemCheckpoint(&_CrtMemState_end);


	if (_CrtMemDifference(&_CrtMemState_diff, &_CrtMemState_start, &_CrtMemState_end))
	{
		_CrtMemDumpStatistics(&_CrtMemState_diff);
	}
#endif
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool Application::initializeCOM(void)
{
	HRESULT hr;


	hr = CoInitialize(nullptr);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void Application::uninitializeCOM(void)
{
	CoUninitialize();
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Application* ApplicationGet(void)
{
	static Application instance;


	return &instance;
}
