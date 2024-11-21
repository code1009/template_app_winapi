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
	_ClassName = className;


	//--------------------------------------------------------------------------
	memset(&_WndClass, 0, sizeof(_WndClass));

	_WndClass.cbSize = sizeof(_WndClass);
	_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = ApplicationGet()->_hInstance;
	_WndClass.lpfnWndProc = WindowProc;
	_WndClass.lpszClassName = _ClassName.c_str();
	_WndClass.lpszMenuName = nullptr;
	_WndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	_WndClass.hCursor = ::LoadCursorW(nullptr, MAKEINTRESOURCEW(32512)); // getInstance()->loadCursor(32512); IDC_ARROW;
	_WndClass.hIcon = nullptr;
	_WndClass.hIconSm = nullptr;



	//--------------------------------------------------------------------------
	WNDCLASSEXW wndClass;
	BOOL rv;


	rv = ::GetClassInfoExW(ApplicationGet()->_hInstance, className, &wndClass);
	if (FALSE == rv)
	{
		ATOM atom = ::RegisterClassExW(&_WndClass);
		if (!atom)
		{
			throw std::runtime_error("WindowClass::registerWindowClass()");
		}
	}
}

void WindowClass::unregisterWindowClass(void)
{

}
