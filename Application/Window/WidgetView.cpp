/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../mwa/RuntimeDebug.hpp"
#include "../mwa/Application.hpp"
#include "../mwa/WindowClass.hpp"
#include "../mwa/Window.hpp"
#include "../mwa/dx2d.hpp"

#include "../Resource/Resource.h"

#include "../Widget/view_window.hpp"

#include "WidgetView.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR WidgetView_ClassName = L"xWidgetView";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WidgetView::WidgetView(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	mwa::WindowClass windowClass;


	windowClass.registerWindowClass(
		WidgetView_ClassName
	);


	//-----------------------------------------------------------------------
	createWindow(hWndParent);


	//-----------------------------------------------------------------------
	_Window = std::make_unique<widget::view_window>(_hWnd);


	//-----------------------------------------------------------------------
	::ShowWindow(_hWnd, SW_SHOW);
	::UpdateWindow(_hWnd);
}

//===========================================================================
LRESULT WidgetView::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

	case WM_HSCROLL:    return OnHScroll(hWnd, uMsg, wParam, lParam);
	case WM_VSCROLL:    return OnVScroll(hWnd, uMsg, wParam, lParam);
	case WM_MOUSEWHEEL: return OnMouseWheel(hWnd, uMsg, wParam, lParam);

	case WM_MOUSEMOVE: return OnMouseMove(hWnd, uMsg, wParam, lParam);

	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void WidgetView::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	LPCWSTR   lpszClassName = WidgetView_ClassName;
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

	//dwStyle |= WS_VSCROLL;
	//dwStyle |= WS_HSCROLL;

	dwExStyle |= WS_EX_CLIENTEDGE;


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
LRESULT WidgetView::onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	RECT rect;

	GetClientRect(hWnd, &rect);


	//-----------------------------------------------------------------------
	UINT cx;
	UINT cy;


	cx = static_cast<UINT>(rect.right - rect.left);
	cy = static_cast<UINT>(rect.bottom - rect.top);


	//-----------------------------------------------------------------------
	if (_Window.get())
	{
		_Window->set_window_size(cx, cy);
	}


	return 0;
}

LRESULT WidgetView::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	if (_Window.get())
	{
		_Window->repaint();
	}


	//-----------------------------------------------------------------------
	// The ValidateRect function validates the client area within a rectangle by
	// removing the rectangle from the update region of the window.
	::ValidateRect(_hWnd, nullptr);

	return 0;
}

LRESULT WidgetView::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
LRESULT WidgetView::OnHScroll(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nSBCode = (int)LOWORD(wParam);
	UINT nPos = (short)(HIWORD(wParam));
	HWND pScrollBar = (HWND)lParam;


	_Window->hscroll(nSBCode);

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::OnVScroll(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nSBCode = (int)LOWORD(wParam);
	UINT nPos = (short)(HIWORD(wParam));
	HWND pScrollBar = (HWND)lParam;


	_Window->vscroll(nSBCode);


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
LRESULT WidgetView::OnMouseWheel(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT  nFlags = (UINT)LOWORD(wParam);
	short zDelta = (short)HIWORD(wParam);
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };


	bool scale = false;


	switch (nFlags)
	{
	case MK_CONTROL:
		scale = true;
		break;

	case MK_LBUTTON:
	case MK_RBUTTON:
		break;
	case MK_MBUTTON:
		break;

	case MK_SHIFT:
		break;

	case MK_XBUTTON1:
	case MK_XBUTTON2:
		break;

	default:
		break;
	}


	if (scale)
	{
		if (zDelta > 0)
		{
			_Window->zoom(true);
		}
		else
		{

			_Window->zoom(false);
		}
	}
	else
	{
		if (zDelta > 0)
		{
			_Window->vscroll(SB_LINEUP);
		}
		else
		{
			_Window->vscroll(SB_LINEDOWN);
		}
	}


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::OnMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int x = GET_X_LPARAM(lParam);
	int y = GET_Y_LPARAM(lParam);


	_Window->set_mouse_position(x, y);

	return 0;
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
	if (_Window.get())
	{
		_Window->repaint();
	}
}




