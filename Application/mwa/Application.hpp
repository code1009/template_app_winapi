/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Application
{
public:
	HINSTANCE _hInstance{ nullptr };
	RuntimeDebug _RuntimeDebug;

public:
	Application() = default;

public:
	virtual ~Application() = default;

public:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	Application(Application&&) = delete;
	Application& operator=(Application&&) = delete;

public:
	virtual bool initialize(HINSTANCE hInstance);
	virtual void terminate(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Application* getApplication(void);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




