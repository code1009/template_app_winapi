/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class RuntimeDebug
{
public:
#ifdef _DEBUG
	typedef struct _MemoryLeackCheck_t
	{
		_CrtMemState start;
		_CrtMemState end;
		_CrtMemState diff;
	}
	MemoryLeackCheck_t;

	MemoryLeackCheck_t _MemoryLeackCheck;
#endif

public:
	RuntimeDebug();

public:
	virtual ~RuntimeDebug();

public:
	void enableMemoryCheck(void);

public:
	void startMemoryLeackCheck(void);
	void endMemoryLeackCheck(void);

public:
	void testMemoryLeack(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





