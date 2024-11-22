/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "../Window/Direct2D.hpp"
#include "../Resource/Resource.h"
#include "WidgetViewRender.hpp"
#include "WidgetView.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR WidgetView_ClassName = L"xWidgetView";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WidgetView::WidgetView(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	WindowClass windowClass;


	windowClass.registerWindowClass(
		WidgetView_ClassName
	);


	//-----------------------------------------------------------------------
	_Render = std::make_unique<WidgetViewRender>();


	//-----------------------------------------------------------------------
	createWindow(hWndParent);


	//-----------------------------------------------------------------------
	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);
}

//===========================================================================
WidgetView::~WidgetView()
{
}

//===========================================================================
LRESULT WidgetView::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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
void WidgetView::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	LPCWSTR lpszClassName = WidgetView_ClassName;
	LPCWSTR lpWindowName  = L"Window";
	DWORD   dwStyle       = ChildWindowStyle;
	DWORD   dwExStyle     = WS_EX_CLIENTEDGE;
	int     X             = CW_USEDEFAULT;
	int     Y             = CW_USEDEFAULT;
	int     nWidth        = CW_USEDEFAULT;
	int     nHeight       = CW_USEDEFAULT;
	HMENU   hMenu         = nullptr;


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
		ApplicationGet()->_hInstance,
		this
	);
	if (nullptr==hWnd)
	{
		throw std::runtime_error("WidgetView::createWindow() failed");
	}
}

void WidgetView::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}
	_hWnd = nullptr;
}

//===========================================================================
LRESULT WidgetView::onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	SIZE size{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	UINT type{ (UINT)wParam };


	//-----------------------------------------------------------------------
	RECT rect;

	GetClientRect(hWnd, &rect);


	//-----------------------------------------------------------------------
	UINT cx;
	UINT cy;


	cx = static_cast<UINT>(rect.right - rect.left);
	cy = static_cast<UINT>(rect.bottom - rect.top);


	//-----------------------------------------------------------------------
	if (_Render.get())
	{
		_Render->resize(_hWnd, cx, cy);
	}


	return 0;
}

LRESULT WidgetView::onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	if (_Render.get())
	{
		_Render->render(_hWnd);
	}


	//-----------------------------------------------------------------------
	// The ValidateRect function validates the client area within a rectangle by
	// removing the rectangle from the update region of the window.
	::ValidateRect(_hWnd, nullptr);

	return 0;
}

LRESULT WidgetView::onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void WidgetView::onIdle(void)
{
	//-----------------------------------------------------------------------
#if 0
	OutputDebugStringW(L"WidgetView::onIdle()\r\n");
	Sleep(10);
#endif


	//-----------------------------------------------------------------------
	if (_Render.get())
	{
		_Render->render(_hWnd);
	}
}




