/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "mwa/RuntimeDebug.hpp"
#include "mwa/Application.hpp"
#include "mwa/WindowClass.hpp"
#include "mwa/Window.hpp"
#include "mwa/MsgLoop.hpp"
#include "mwa/dx2d.hpp"
#include "mwa/Splitter.hpp"

#include "Widget/view_window.hpp"

#include "Window/WidgetView.hpp"
#include "Window/WidgetTool.hpp"
#include "Window/LogView.hpp"
#include "Window/PropertyBox.hpp"
#include "Window/MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class App : public mwa::Application
{
public:
	App();
	
public:
	virtual ~App();

public:
	virtual bool initialize(HINSTANCE hInstance);
	virtual void terminate(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
App::App()
{
}

App::~App()
{
}

bool App::initialize(HINSTANCE hInstance)
{
	bool rv;
	
	
	rv = mwa::Application::initialize(hInstance);
	if (false == rv)
	{
		return false;
	}


	return true;
}

void App::terminate(void)
{
	mwa::Application::terminate();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{
	Application* getApplication(void)
	{
		static App instance;


		return &instance;
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void RunWindow(void)
{
	MainFrame mainFrame;



	mwa::MsgLoop msgLoop;


	msgLoop.addIdleHandler([&]() { mainFrame.onIdle(); });

	msgLoop.runMsgLoop();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow
)
{
	bool rv;


	rv = mwa::getApplication()->initialize(hInstance);
	if (rv == false)
	{
		return -1;
	}


	try
	{
		RunWindow();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
	}



	mwa::getApplication()->terminate();



	return 0;
}




