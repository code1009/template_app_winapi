/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "RuntimeDebug.hpp"
#include "Application.hpp"
#include "Window.hpp"
#include "WindowClass.hpp"






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void WindowClass::registerWindowClass(
	LPCWSTR className, 
	UINT idMenu, 
	UINT idIcon, UINT idSmallIcon, UINT idCursor, 
	UINT style
)
{
	//-----------------------------------------------------------------------
	_ClassName = className;


	//-----------------------------------------------------------------------
	memset(&_WndClass, 0, sizeof(_WndClass));

	_WndClass.cbSize        = sizeof(_WndClass);
	//_WndClass.style       = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS
	_WndClass.style         = style;
	_WndClass.cbClsExtra    = 0;
	_WndClass.cbWndExtra    = 0;
	_WndClass.hInstance     = getApplication()->_hInstance;
	_WndClass.lpfnWndProc   = WindowProc;
	_WndClass.lpszClassName = _ClassName.c_str();
	_WndClass.lpszMenuName  = MAKEINTRESOURCEW(idMenu);
	_WndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	_WndClass.hCursor       = ::LoadCursorW(nullptr, MAKEINTRESOURCEW(idCursor));
	_WndClass.hIcon         = ::LoadIconW(getApplication()->_hInstance, MAKEINTRESOURCEW(idIcon));
	_WndClass.hIconSm       = ::LoadIconW(getApplication()->_hInstance, MAKEINTRESOURCEW(idSmallIcon));



	//-----------------------------------------------------------------------
	WNDCLASSEXW wndClass;
	BOOL rv;


	rv = ::GetClassInfoExW(getApplication()->_hInstance, className, &wndClass);
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
	BOOL rv;


	rv = ::UnregisterClassW(_ClassName.c_str(), getApplication()->_hInstance);
	if (FALSE == rv)
	{
		throw std::runtime_error("WindowClass::unregisterWindowClass()");
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




