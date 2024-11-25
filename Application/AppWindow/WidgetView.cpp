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

	case WM_HSCROLL:        return OnHScroll(hWnd, uMsg, wParam, lParam);
	case WM_VSCROLL:        return OnVScroll(hWnd, uMsg, wParam, lParam);
	case WM_MOUSEWHEEL:     return OnMouseWheel(hWnd, uMsg, wParam, lParam);

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
	DWORD   dwExStyle     = ChildWindowStyleEx;
	int     X             = CW_USEDEFAULT;
	int     Y             = CW_USEDEFAULT;
	int     nWidth        = CW_USEDEFAULT;
	int     nHeight       = CW_USEDEFAULT;
	HMENU   hMenu         = nullptr;


	dwStyle |= WS_VSCROLL;
	dwStyle |= WS_HSCROLL;

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
LRESULT WidgetView::OnHScroll(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nSBCode = (int)LOWORD(wParam);
	UINT nPos = (short)(HIWORD(wParam));
	HWND pScrollBar = (HWND)lParam;


	//_Render->hscroll(nSBCode);
	OutputDebugStringW(L"WidgetView::OnHScroll()\r\n");

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetView::OnVScroll(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT nSBCode = (int)LOWORD(wParam);
	UINT nPos = (short)(HIWORD(wParam));
	HWND pScrollBar = (HWND)lParam;


	//_Render->vscroll(nSBCode);
	OutputDebugStringW(L"WidgetView::OnVScroll()\r\n");


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
LRESULT WidgetView::OnMouseWheel(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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
			OutputDebugStringW(L"WidgetView::OnMouseWheel(): zoomin\r\n");
			//_Render->zoom(true);
		}
		else
		{

			//_Render->zoom(false);
			OutputDebugStringW(L"WidgetView::OnMouseWheel(): zoomout\r\n");
		}
	}
	else
	{
		if (zDelta > 0)
		{
			//_Render->vscroll(SB_LINEUP);
			OutputDebugStringW(L"WidgetView::OnMouseWheel(): SB_LINEUP\r\n");
		}
		else
		{
			//_Render->vscroll(SB_LINEDOWN);
			OutputDebugStringW(L"WidgetView::OnMouseWheel(): SB_LINEDOWN\r\n");
		}
	}


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




