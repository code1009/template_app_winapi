////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "Window/Application.hpp"
#include "Window/WindowClass.hpp"
#include "Window/Window.hpp"
#include "Window/WindowMsgLoop.hpp"

#include "AppWindow/MainWindow.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
void RunWindow()
{
	MainWindow mainWindow;



	WindowMsgLoop windowMsgLoop;


	windowMsgLoop.run();
}





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow
)
{
	ApplicationGet()->initInstance(hInstance);



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



	ApplicationGet()->termInstance();



	return 0;
}
