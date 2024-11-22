////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "../Window/Direct2D.hpp"
#include "../Resource/Resource.h"
#include "View.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
constexpr LPCWSTR View_ClassName = L"xView";





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
View::View(HWND hWndParent)
{
	//--------------------------------------------------------------------------
	WindowClass windowClass;


	windowClass.registerWindowClass(
		View_ClassName
	);


	//--------------------------------------------------------------------------
	_Direct2D = std::make_unique<Direct2D>();


	//--------------------------------------------------------------------------
	createWindow(hWndParent);

	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);
}

//==============================================================================
View::~View()
{
}

//==============================================================================
LRESULT View::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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

//==============================================================================
void View::createWindow(HWND hWndParent)
{
	//--------------------------------------------------------------------------
	//HWND    hWndParent    = nullptr;
	LPCWSTR lpszClassName = View_ClassName;
	LPCWSTR lpWindowName  = L"Window";
	DWORD   dwStyle       = ChildWindowStyle;
	DWORD   dwExStyle     = ChildWindowStyleEx;
	int     X             = CW_USEDEFAULT;
	int     Y             = CW_USEDEFAULT;
	int     nWidth        = CW_USEDEFAULT;
	int     nHeight       = CW_USEDEFAULT;
	HMENU   hMenu         = nullptr;


	//--------------------------------------------------------------------------
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
		ApplicationGet()->_hInstance,
		this
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

//==============================================================================
LRESULT View::onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//--------------------------------------------------------------------------
	SIZE size{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	UINT type{ (UINT)wParam };


	//--------------------------------------------------------------------------
	RECT rect;

	GetClientRect(hWnd, &rect);


	//--------------------------------------------------------------------------
	if (_Direct2D.get())
	{
		UINT cx;
		UINT cy;


		cx = static_cast<UINT>(rect.right  - rect.left);
		cy = static_cast<UINT>(rect.bottom - rect.top );

		_Direct2D->resize(_hWnd, cx, cy);
	}


	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//return TRUE;
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

#if 0
LRESULT View::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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
#endif

LRESULT View::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	if (_Direct2D.get())
	{
		_Direct2D->render(_hWnd);
	}


	// The ValidateRect function validates the client area within a rectangle by
	// removing the rectangle from the update region of the window.
	::ValidateRect(_hWnd, nullptr);


	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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

//==============================================================================
void View::onIdle(void)
{
	OutputDebugStringW(L"View::onIdle()\r\n");
	Sleep(10);


}
