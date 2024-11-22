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
#include "LogView.hpp"
#include "MainFrame.hpp"
#include "AboutBox.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR MainFrame_ClassName = L"xMainFrame";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
MainFrame::MainFrame()
{
	//-----------------------------------------------------------------------
	WindowClass windowClass;


	windowClass.registerWindowClass(
		MainFrame_ClassName, 
		IDC_MAINFRAME, 
		IDI_MAINFRAME, IDI_SMALL
	);


	//-----------------------------------------------------------------------
	createWindow();


	//-----------------------------------------------------------------------
	_WidgetView = std::make_unique<WidgetView>(_hWnd);
	_LogView = std::make_unique<LogView>(_hWnd);


	//-----------------------------------------------------------------------
	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);
}

//===========================================================================
MainFrame::~MainFrame()
{
}

//===========================================================================
LRESULT MainFrame::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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

	switch (uMsg)
	{
	case WM_LBUTTONDOWN: _Splitter.onLButtonDown(hWnd, uMsg, wParam, lParam); return 0;
	case WM_MOUSEMOVE  : _Splitter.onMouseMove(hWnd, uMsg, wParam, lParam); return 0;
	case WM_LBUTTONUP  : _Splitter.onLButtonUp(hWnd, uMsg, wParam, lParam); return 0;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void MainFrame::createWindow(void)
{
	HWND    hWndParent    = nullptr;
	LPCWSTR lpszClassName = MainFrame_ClassName;
	LPCWSTR lpWindowName  = L"Window";
	DWORD   dwStyle       = WS_OVERLAPPEDWINDOW; // FrameWindowStyle;
	DWORD   dwExStyle     = FrameWindowStyleEx;
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
		throw std::runtime_error("MainFrame::createWindow() failed");
	}
}

void MainFrame::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}
	_hWnd = nullptr;
}

//===========================================================================
LRESULT MainFrame::onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	::PostQuitMessage(0);

	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//destroyWindow();

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
LRESULT MainFrame::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	SIZE size { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	UINT type { (UINT)wParam };


	//-----------------------------------------------------------------------
	RECT rect;


	GetClientRect(hWnd, &rect);


	//-----------------------------------------------------------------------
	UINT cx;
	UINT cy;


	cx = static_cast<UINT>(rect.right - rect.left);
	cy = static_cast<UINT>(rect.bottom - rect.top);


	//-----------------------------------------------------------------------
	if (_WidgetView.get() && _LogView.get())
#if 0
	{
		constexpr int logViewHeight = 200;


		if (cy > logViewHeight)
		{
			::MoveWindow(_WidgetView->_hWnd, 0, 0, cx, cy - logViewHeight, TRUE);

			::MoveWindow(_LogView->_hWnd, 0, cy - logViewHeight, cx, logViewHeight, TRUE);
		}
		else
		{
			::MoveWindow(_WidgetView->_hWnd, 0, 0, 0, 0, TRUE);

			::MoveWindow(_LogView->_hWnd, 0, 0, cx, cy, TRUE);
		}
	}
#endif
	{
		int _w0;
		int _w1;

		_w0 = static_cast<int>(     (cy * _Splitter._percent) - (_Splitter._Width / 2));
		_w1 = static_cast<int>(cy - (cy * _Splitter._percent) - (_Splitter._Width / 2));

		::MoveWindow(_WidgetView->_hWnd, 0,                      0, cx, _w0, TRUE);
		::MoveWindow(_LogView   ->_hWnd, 0, _w0 + _Splitter._Width, cx, _w1, TRUE);
	}

	//-----------------------------------------------------------------------
	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
#if 0
	PAINTSTRUCT ps;
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 0, 0, L"MainFrame", 9);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return 0;
#endif
	
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	int id = LOWORD(wParam);


	switch (id)
	{
	case IDM_APP_ABOUT:
		onCommand_App_About();
		return 0;

	case IDM_APP_EXIT:
		onCommand_App_Exit();
		return 0;

	default:
		if (_WidgetView.get())
		{
			return ::SendMessage(_WidgetView->_hWnd, uMsg, wParam, lParam);
		}
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

void MainFrame::onCommand_App_About(void)
{
	AboutBox aboutBox;
	INT_PTR rv;


	rv = DialogBoxParamW(
		ApplicationGet()->_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), 
		_hWnd, 
		DialogProc,
		reinterpret_cast<LPARAM>(&aboutBox)
	);
	switch (rv)
	{
	case IDOK:
		break;

	case IDCANCEL:
		break;

	default:
		break;
	}
}

void MainFrame::onCommand_App_Exit(void)
{
	destroyWindow();
}

LRESULT MainFrame::onNotify(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
#if 0
	NMHDR* hdr = reinterpret_cast<NMHDR*>(lParam);


	switch (hdr->code)
	{
	default:
		break;
	}
#endif


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void MainFrame::onIdle(void)
{
	if (_WidgetView.get())
	{
		_WidgetView->onIdle();
	}
}




