////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "Window/Application.hpp"
#include "Window/WindowClass.hpp"
#include "Window/Window.hpp"
#include "Window/MsgLoop.hpp"

#include "AppWindow/View.hpp"
#include "AppWindow/MainFrame.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
void RunWindow(void)
{
	MainFrame mainFrame;



	MsgLoop msgLoop;


	msgLoop.addIdleHandler([&]() { mainFrame.onIdle(); });

	msgLoop.runMsgLoop();
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
