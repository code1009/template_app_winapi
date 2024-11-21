////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "Application.hpp"
#include "WindowClass.hpp"
#include "Window.hpp"






////////////////////////////////////////////////////////////////////////////////
//==============================================================================
WindowClass::WindowClass()
{
}

//==============================================================================
WindowClass::~WindowClass()
{
}

//==============================================================================
void WindowClass::registerWindowClass(LPCWSTR className, UINT iconId)
{
	//--------------------------------------------------------------------------
	memset(&_WindowClass, 0, sizeof(_WindowClass));

	_WindowClass.cbSize = sizeof(_WindowClass);
	_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	_WindowClass.cbClsExtra = 0;
	_WindowClass.cbWndExtra = 0;
	_WindowClass.hInstance = ApplicationGet()->_hInstance;
	_WindowClass.lpfnWndProc = WindowProc;
	_WindowClass.lpszClassName = className;
	_WindowClass.lpszMenuName = nullptr;
	_WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	_WindowClass.hCursor = ::LoadCursorW(nullptr, MAKEINTRESOURCEW(32512)); // getInstance()->loadCursor(32512); IDC_ARROW;
	_WindowClass.hIcon = nullptr;
	_WindowClass.hIconSm = nullptr;



	//--------------------------------------------------------------------------
	WNDCLASSEXW wndClass;
	BOOL rv;


	rv = ::GetClassInfoExW(ApplicationGet()->_hInstance, className, &wndClass);
	if (FALSE == rv)
	{
		ATOM atom = ::RegisterClassExW(&_WindowClass);
		if (!atom)
		{
			throw std::runtime_error("WindowClass::registerWindowClass()");
		}
	}
}

void WindowClass::unregisterWindowClass(void)
{

}
