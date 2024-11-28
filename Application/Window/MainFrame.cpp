/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../mwa/RuntimeDebug.hpp"
#include "../mwa/Application.hpp"
#include "../mwa/WindowClass.hpp"
#include "../mwa/Window.hpp"
#include "../mwa/Splitter.hpp"
#include "../mwa/dx2d.hpp"

#include "../Resource/Resource.h"

#include "../Widget/view_window.hpp"

#include "WidgetView.hpp"
#include "WidgetTool.hpp"
#include "LogView.hpp"
#include "PropertyBox.hpp"
#include "MainFrame.hpp"
#include "AboutBox.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR MainFrame_ClassName = L"xMainFrame";
constexpr UINT MainFrame_Timer_ID = 100;
constexpr UINT MainFrame_Timer_Time = 100;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
MainFrame::MainFrame()
{
	//-----------------------------------------------------------------------
	mwa::WindowClass windowClass;


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
	_WidgetToolFrame = std::make_unique<WidgetToolFrame>(_hWnd);
	_PropertyBox = std::make_unique<PropertyBox>(_hWnd);


	//-----------------------------------------------------------------------
	::ShowWindow(_hWnd, SW_SHOW);
	::UpdateWindow(_hWnd);
}

//===========================================================================
LRESULT MainFrame::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_TIMER:      return onTimer     (hWnd, uMsg, wParam, lParam);

	case WM_USER+0:     return onUser0(hWnd, uMsg, wParam, lParam);

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
	HWND      hWndParent    = nullptr;
	LPCWSTR   lpszClassName = MainFrame_ClassName;
	LPCWSTR   lpWindowName  = L"Window";
	DWORD     dwStyle       = mwa::FrameWindowStyle;
	DWORD     dwExStyle     = mwa::FrameWindowStyleEx;
	int       X             = CW_USEDEFAULT;
	int       Y             = CW_USEDEFAULT;
	int       nWidth        = CW_USEDEFAULT;
	int       nHeight       = CW_USEDEFAULT;
	HMENU     hMenu         = nullptr;
	HINSTANCE hInstance     = mwa::getApplication()->_hInstance;
	LPVOID    lpParam       = this;


	dwStyle = WS_OVERLAPPEDWINDOW;


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
LRESULT MainFrame::onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	::SetTimer(hWnd, MainFrame_Timer_ID, MainFrame_Timer_Time, nullptr);

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	::KillTimer(hWnd, MainFrame_Timer_ID);

	::PostQuitMessage(0);

	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//destroyWindow();

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
LRESULT MainFrame::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		_Splitter.UpdateLayout(_hWnd, _WidgetView->_hWnd, _LogView->_hWnd);
	}


	//-----------------------------------------------------------------------
	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	_Splitter.Draw(hWnd);
	return TRUE;
//	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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


	RECT rect;
	GetClientRect(hWnd, &rect);

	const HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 255));
	const HPEN hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 255));

	const HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
	const HGDIOBJ hOldPen = SelectObject(hdc, hPen);

	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);

	DeleteObject(hBrush);
	DeleteObject(hPen);


	::EndPaint(hWnd, &ps);


	return 0;
#endif

#if 1
	LRESULT rv = 0;


	rv = ::DefWindowProcW(hWnd, uMsg, wParam, lParam);

	//_Splitter.Draw(hWnd);

	return  rv;
#endif
}

LRESULT MainFrame::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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


	rv = aboutBox.doModal(_hWnd);
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

LRESULT MainFrame::onNotify(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT MainFrame::onTimer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT id = (UINT)wParam;


	if(MainFrame_Timer_ID == id)
	{
		onIdle();
	}


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onUser0(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	std::uint32_t id;


	id = static_cast<std::uint32_t>(wParam);
	switch (id)
	{
	case 1:
		_WidgetToolFrame.reset();
		//_WidgetToolFrame = std::make_unique<WidgetToolFrame>(_hWnd);
		break;

	case 2:
		_PropertyBox.reset();
		break;

	default:
		break;
	}

	return 0;
}

//===========================================================================
void MainFrame::onIdle(void)
{
	if (_WidgetView.get())
	{
		_WidgetView->onIdle();
	}
}




