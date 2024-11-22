/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Application
{
public:
	HINSTANCE _hInstance{ nullptr };

public:
	Application();

public:
	virtual ~Application();

public:
	bool initialize(HINSTANCE hInstance);
	void terminate(void);

public:
	void enableDebugRuntimeMemoryCheck(void);
	void startDebugRuntimeMemoryLeackCheck(void);
	void endDebugRuntimeMemoryLeackCheck(void);

public:
	bool initializeCOM(void);
	void uninitializeCOM(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Application* ApplicationGet(void);




