/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../mwa/RuntimeDebug.hpp"
#include "../mwa/Application.hpp"
#include "../mwa/WindowClass.hpp"
#include "../mwa/Window.hpp"

#include "../Resource/Resource.h"

#include "View.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR View_ClassName = L"xView";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
View::View(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	mwa::WindowClass windowClass;


	windowClass.registerWindowClass(
		View_ClassName
	);


	//-----------------------------------------------------------------------
	createWindow(hWndParent);


	//-----------------------------------------------------------------------
	::ShowWindow(_hWnd, SW_SHOW);
	::UpdateWindow(_hWnd);
}

//===========================================================================
LRESULT View::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:     return onCreate    (hWnd, uMsg, wParam, lParam);
	case WM_DESTROY:    return onDestroy   (hWnd, uMsg, wParam, lParam);
	case WM_CLOSE:      return onClose     (hWnd, uMsg, wParam, lParam);
	case WM_SIZE:       return onSize      (hWnd, uMsg, wParam, lParam);
	case WM_ERASEBKGND: return onEraseBkGnd(hWnd, uMsg, wParam, lParam);
	case WM_PAINT:      return onPaint     (hWnd, uMsg, wParam, lParam);
	case WM_COMMAND:    return onCommand   (hWnd, uMsg, wParam, lParam);
	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void View::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	//HWND    hWndParent    = nullptr;
	LPCWSTR   lpszClassName = View_ClassName;
	LPCWSTR   lpWindowName  = L"Window";
	DWORD     dwStyle       = mwa::ChildWindowStyle;
	DWORD     dwExStyle     = mwa::ChildWindowStyleEx;
	int       X             = CW_USEDEFAULT;
	int       Y             = CW_USEDEFAULT;
	int       nWidth        = CW_USEDEFAULT;
	int       nHeight       = CW_USEDEFAULT;
	HMENU     hMenu         = nullptr;
	HINSTANCE hInstance     = mwa::getApplication()->_hInstance;
	LPVOID    lpParam       = this;

	//-----------------------------------------------------------------------
	HWND hWnd;


	hWnd = ::CreateWindowExW(
		dwExStyle,
		lpszClassName,
		lpWindowName,
		dwStyle,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		hInstance,
		lpParam
	);
	if (nullptr==hWnd)
	{
		throw std::runtime_error("View::createWindow() failed");
	}
}

void View::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}

	_hWnd = nullptr;
}

//===========================================================================
LRESULT View::onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//return TRUE;
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 0, 0, L"View", 4);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int id = LOWORD(wParam);

	switch (id)
	{
	case IDM_APP_ABOUT:
		onCommand_App_About();
		return 0;

	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

void View::onCommand_App_About(void)
{
	MessageBoxW(
		_hWnd,
		L"App_About",
		L"App_About",
		MB_OK
	);
}




