////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "Application.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
Application::Application()
{
}

//==============================================================================
Application::~Application()
{
}

//==============================================================================
void Application::initInstance(HINSTANCE hInstance)
{
	_hInstance = hInstance;

	DebugRuntimeMemoryCheck_enable();
	DebugRuntimeMemoryLeackCheck_start();
}

void Application::termInstance(void)
{
	DebugRuntimeMemoryLeackCheck_end();

	_hInstance = nullptr;
}

//==============================================================================
void Application::DebugRuntimeMemoryCheck_enable(void)
{
	//--------------------------------------------------------------------------
#ifdef _DEBUG
	// Enable run-time memory check for debug builds.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


	//--------------------------------------------------------------------------
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

//==============================================================================
#ifdef _DEBUG
static _CrtMemState _CrtMemState_start;
static _CrtMemState _CrtMemState_end;
static _CrtMemState _CrtMemState_diff;
#endif

//==============================================================================
void Application::DebugRuntimeMemoryLeackCheck_start(void)
{
	//--------------------------------------------------------------------------
#ifdef _DEBUG
	_CrtMemCheckpoint(&_CrtMemState_start);
#endif


	//--------------------------------------------------------------------------
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

void Application::DebugRuntimeMemoryLeackCheck_end(void)
{
#ifdef _DEBUG
	_CrtMemCheckpoint(&_CrtMemState_end);


	if (_CrtMemDifference(&_CrtMemState_diff, &_CrtMemState_start, &_CrtMemState_end))
	{
		_CrtMemDumpStatistics(&_CrtMemState_diff);
	}
#endif
}





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
Application* ApplicationGet(void)
{
	static Application instance;


	return &instance;
}