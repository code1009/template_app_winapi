/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../mwa/RuntimeDebug.hpp"
#include "../mwa/Application.hpp"
#include "../mwa/WindowClass.hpp"
#include "../mwa/Window.hpp"

#include "../Resource/Resource.h"

#include "WidgetTool.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR WidgetToolView_ClassName = L"xWidgetToolView";




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WidgetToolView::WidgetToolView(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	mwa::WindowClass windowClass;


	windowClass.registerWindowClass(
		WidgetToolView_ClassName
	);


	//-----------------------------------------------------------------------
	createWindow(hWndParent);


	//-----------------------------------------------------------------------
	::ShowWindow(_hWnd, SW_SHOW);
	::UpdateWindow(_hWnd);
}

//===========================================================================
LRESULT WidgetToolView::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:     return onCreate       (hWnd, uMsg, wParam, lParam);
	case WM_DESTROY:    return onDestroy      (hWnd, uMsg, wParam, lParam);
	case WM_CLOSE:      return onClose        (hWnd, uMsg, wParam, lParam);
	case WM_SIZE:       return onSize         (hWnd, uMsg, wParam, lParam);
	case WM_ERASEBKGND: return onEraseBkGnd   (hWnd, uMsg, wParam, lParam);
	case WM_PAINT:      return onPaint        (hWnd, uMsg, wParam, lParam);
	case WM_COMMAND:    return onCommand      (hWnd, uMsg, wParam, lParam);
	case OCM_NOTIFY:    return OnNotifyReflect(hWnd, uMsg, wParam, lParam);
	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void WidgetToolView::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	LPCWSTR   lpszClassName = WidgetToolView_ClassName;
	LPCWSTR   lpWindowName  = L"Window";
	DWORD     dwStyle       = mwa::ControlWindowStyle;
	DWORD     dwExStyle     = mwa::ControlWindowStyleEx;
	int       X             = 0;
	int       Y             = 0;
	int       nWidth        = 0;
	int       nHeight       = 0;
	HMENU     hMenu         = nullptr;
	HINSTANCE hInstance     = mwa::getApplication()->_hInstance;
	LPVOID    lpParam       = this;

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
	if (nullptr == hWnd)
	{
		throw std::runtime_error("WidgetToolView::createWindow() failed");
	}
}

void WidgetToolView::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}
	_hWnd = nullptr;
}

//===========================================================================
LRESULT WidgetToolView::onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolView::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolView::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolView::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolView::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolView::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
}

LRESULT WidgetToolView::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
LRESULT WidgetToolView::OnNotifyReflect(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if 0
	NMHDR* hdr = reinterpret_cast<NMHDR*>(lParam);


	switch (hdr->code)
	{
		break;

	default:
		break;
	}
#endif


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR WidgetToolFrame_ClassName = L"xWidgetToolFrame";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WidgetToolFrame::WidgetToolFrame(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	_hWndParent = hWndParent;

	//-----------------------------------------------------------------------
	mwa::WindowClass windowClass;


	windowClass.registerWindowClass(
		WidgetToolFrame_ClassName,
		0,
		IDI_SMALL,
		IDI_SMALL
	);


	//-----------------------------------------------------------------------
	createWindow(hWndParent);


	//-----------------------------------------------------------------------
	_View = std::make_unique<WidgetToolView>(_hWnd);


	//-----------------------------------------------------------------------
	::ShowWindow(_hWnd, SW_SHOW);
	::UpdateWindow(_hWnd);
}

//===========================================================================
LRESULT WidgetToolFrame::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_NOTIFY:     return onNotify    (hWnd, uMsg, wParam, lParam);
	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void WidgetToolFrame::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	int window_x;
	int window_y;
	int window_client_cx;
	int window_client_cy;


	window_x = 0;
	window_y = 0;
	window_client_cx = 160;
	window_client_cy = 400;


	//-----------------------------------------------------------------------
	RECT ParentRect;
	

	GetWindowRect(hWndParent, &ParentRect);



	//-----------------------------------------------------------------------
	//HWND      hWndParent    = nullptr;
	LPCWSTR   lpszClassName = WidgetToolFrame_ClassName;
	LPCWSTR   lpWindowName  = L"Window";
	DWORD     dwStyle       = mwa::ToolWindowStyle;
	DWORD     dwExStyle     = mwa::ToolWindowStyleEx;
	int       X             = 0;
	int       Y             = 0;
	int       nWidth        = 0;
	int       nHeight       = 0;
	HMENU     hMenu         = nullptr;
	HINSTANCE hInstance     = mwa::getApplication()->_hInstance;
	LPVOID    lpParam       = this;


	dwStyle = 0
		| WS_OVERLAPPED
		| WS_CAPTION
		| WS_SIZEBOX
		//| WS_SYSMENU
		| WS_CLIPCHILDREN
		| WS_CLIPSIBLINGS
		;

	//-----------------------------------------------------------------------
	int cxEdge = GetSystemMetrics(SM_CXEDGE);
	int cyEdge = GetSystemMetrics(SM_CYEDGE);

	int cxSizeFrame = GetSystemMetrics(SM_CXSIZEFRAME);
	int cySizeFrame = GetSystemMetrics(SM_CYSIZEFRAME);
	
	int cyCaption = GetSystemMetrics(SM_CYCAPTION);
	int cyMenu = GetSystemMetrics(SM_CYMENU);

	int cxSpace = 20;
	int cySpace = 20;


	//-----------------------------------------------------------------------
	RECT rect = { 0, 0, window_client_cx, window_client_cy };

	
	// Adjust the window size to include the non-client area
	if (AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle))
	{
		X = ParentRect.left + cxSpace + cxEdge + cxSizeFrame;
		Y = ParentRect.top  + cySpace + cyEdge + cxSizeFrame + cyCaption + cyMenu;
		nWidth  = rect.right  - rect.left;
		nHeight = rect.bottom - rect.top;
	}
	else
	{
		X = ParentRect.left + cxSpace + cxEdge + cxSizeFrame;
		Y = ParentRect.top  + cySpace + cyEdge + cxSizeFrame + cyCaption + cyMenu;
		nWidth  = window_client_cx + 10;
		nHeight = window_client_cy + 10;
	}


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
		throw std::runtime_error("WidgetToolFrame::createWindow() failed");
	}
}

void WidgetToolFrame::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}
	_hWnd = nullptr;
}

//===========================================================================
LRESULT WidgetToolFrame::onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolFrame::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (::IsWindow(_hWndParent))
	{
		PostMessage(_hWndParent, WM_USER + 0, 1, 0);
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolFrame::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolFrame::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	if(_View.get())
	{
		::MoveWindow(_View->_hWnd, 0, 0, cx, cy, TRUE);
	}

	return 0;
}

LRESULT WidgetToolFrame::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolFrame::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if 0
	PAINTSTRUCT ps;
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 0, 0, L"WidgetToolFrame", 15);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return 0;
#endif
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolFrame::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT WidgetToolFrame::onNotify(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	NMHDR* hdr = reinterpret_cast<NMHDR*>(lParam);


	if (_View.get())
	{
		if (hdr->hwndFrom == _View->_hWnd)
		{
			return ::SendMessage(_View->_hWnd, OCM_NOTIFY, wParam, lParam);
		}
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}



