////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#pragma once





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
class Application
{
public:
	HINSTANCE _hInstance{ nullptr };

public:
	Application();
	~Application();

public:
	void initInstance(HINSTANCE hInstance);
	void termInstance(void);

public:
	void DebugRuntimeMemoryCheck_enable(void);
	void DebugRuntimeMemoryLeackCheck_start(void);
	void DebugRuntimeMemoryLeackCheck_end(void);
};





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
Application* ApplicationGet(void);




