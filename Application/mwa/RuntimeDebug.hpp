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
	RuntimeDebug() = default;

public:
	virtual ~RuntimeDebug() = default;

public:
	RuntimeDebug(const RuntimeDebug&) = delete;
	RuntimeDebug& operator=(const RuntimeDebug&) = delete;

	RuntimeDebug(RuntimeDebug&&) = delete;
	RuntimeDebug& operator=(RuntimeDebug&&) = delete;

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





