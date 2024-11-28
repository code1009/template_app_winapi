/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "RuntimeDebug.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void RuntimeDebug::enableMemoryCheck(void)
{
#ifdef _DEBUG
	// Enable run-time memory check for debug builds.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//testMemoryLeack();
#endif
}

void RuntimeDebug::startMemoryLeackCheck(void)
{
#ifdef _DEBUG
	_CrtMemCheckpoint(&_MemoryLeackCheck.start);

	//testMemoryLeack();
#endif
}

void RuntimeDebug::endMemoryLeackCheck(void)
{
#ifdef _DEBUG
	_CrtMemCheckpoint(&_MemoryLeackCheck.end);


	if (_CrtMemDifference(&_MemoryLeackCheck.diff, &_MemoryLeackCheck.start, &_MemoryLeackCheck.end))
	{
		_CrtMemDumpStatistics(&_MemoryLeackCheck.diff);
	}
#endif
}

void RuntimeDebug::testMemoryLeack(void)
{
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
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




