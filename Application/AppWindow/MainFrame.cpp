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
VSplitter::VSplitter()
{
	_Color = GetSysColor(COLOR_BTNFACE);
	_Percent = 0.8;
}

void VSplitter::Draw(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);


	const int maxValue = rect.bottom;


	const int curValue = static_cast<int>(maxValue * _Percent);
	Draw(hWnd, curValue);
}

void VSplitter::Draw(HWND hWnd, int curPos)
{
	const HDC hdc = GetDC(hWnd);


	if (nullptr == hdc)
	{
		return;
	}


	const HBRUSH hBrush = CreateSolidBrush(_Color);
	const HPEN   hPen = CreatePen(PS_SOLID, 1, _Color);


	if (nullptr == hBrush)
	{
		ReleaseDC(hWnd, hdc);
		return;
	}
	if (nullptr == hPen)
	{
		DeleteObject(hBrush);
		ReleaseDC(hWnd, hdc);
		return;
	}


	RECT rect;
	GetClientRect(hWnd, &rect);


	RECT barRect;
	barRect.left = 0;
	barRect.top = curPos - _Width / 2;
	barRect.right = rect.right;
	barRect.bottom = curPos + _Width / 2;


	//SetROP2(hdc, R2_NOT);
	//SetBkMode(hdc, TRANSPARENT);

	const HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
	const HGDIOBJ hOldPen = SelectObject(hdc, hPen);

	Rectangle(hdc, barRect.left, barRect.top, barRect.right, barRect.bottom);

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);

	DeleteObject(hBrush);
	DeleteObject(hPen);

	ReleaseDC(hWnd, hdc);
}

void VSplitter::UpdateLayout(HWND hWnd, HWND hFirstWnd, HWND hSecondWnd)
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
	int first;
	int second;


	first = static_cast<int>((cy * _Percent) - (_Width / 2));
	second = static_cast<int>(cy - (cy * _Percent) - (_Width / 2));

	::MoveWindow(hFirstWnd, 0, 0, cx, first, TRUE);
	::MoveWindow(hSecondWnd, 0, first + _Width, cx, second, TRUE);
}

void VSplitter::onLButtonDown(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	SetCapture(hWnd);
	_OldPos = -1;
}

void VSplitter::onLButtonUp(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetCapture() != hWnd)
	{
		return;
	}

	ReleaseCapture();

	if (_OldPos > 0)
	{
		Draw(hWnd, _OldPos);
	}

	SendMessage(hWnd, WM_SIZE, 0, 0);
}

void VSplitter::onMouseMove(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetCapture() != hWnd)
	{
		return;
	}


	RECT rect;
	GetClientRect(hWnd, &rect);


	const int posValue = GET_Y_LPARAM(lParam);
	const int maxValue = rect.bottom;
	_Percent = static_cast<double>(posValue) / static_cast<double>(maxValue);


	if (_Percent < 0.1)
	{
		_Percent = 0.1;
	}
	else if (_Percent > 0.9)
	{
		_Percent = 0.9;
	}


	const int curValue = static_cast<int>(maxValue * _Percent);
	if (_OldPos != curValue)
	{
		if (_OldPos > 0)
		{
			Draw(hWnd, _OldPos);
		}

		Draw(hWnd, curValue);
		_OldPos = curValue;
	}


	SendMessage(hWnd, WM_SIZE, 0, 0);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
HSplitter::HSplitter()
{
	_Color = GetSysColor(COLOR_BTNFACE);
	_Percent = 0.8;
}

void HSplitter::Draw(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);


	const int maxValue = rect.right;


	const int curValue = static_cast<int>(maxValue * _Percent);
	Draw(hWnd, curValue);
}

void HSplitter::Draw(HWND hWnd, int curPos)
{
	const HDC hdc = GetDC(hWnd);


	if (nullptr == hdc)
	{
		return;
	}


	const HBRUSH hBrush = CreateSolidBrush(_Color);
	const HPEN   hPen = CreatePen(PS_SOLID, 1, _Color);


	if (nullptr == hBrush)
	{
		ReleaseDC(hWnd, hdc);
		return;
	}
	if (nullptr == hPen)
	{
		DeleteObject(hBrush);
		ReleaseDC(hWnd, hdc);
		return;
	}


	RECT rect;
	GetClientRect(hWnd, &rect);


	RECT barRect;
	barRect.top = 0;
	barRect.left = curPos - _Width / 2;
	barRect.bottom = rect.right;
	barRect.right = curPos + _Width / 2;


	//SetROP2(hdc, R2_NOT);
	//SetBkMode(hdc, TRANSPARENT);

	const HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
	const HGDIOBJ hOldPen = SelectObject(hdc, hPen);

	Rectangle(hdc, barRect.left, barRect.top, barRect.right, barRect.bottom);

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);

	DeleteObject(hBrush);
	DeleteObject(hPen);

	ReleaseDC(hWnd, hdc);
}

void HSplitter::UpdateLayout(HWND hWnd, HWND hFirstWnd, HWND hSecondWnd)
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
	int first;
	int second;


	first = static_cast<int>((cx * _Percent) - (_Width / 2));
	second = static_cast<int>(cx - (cx * _Percent) - (_Width / 2));

	::MoveWindow(hFirstWnd, 0, 0, first, cy, TRUE);
	::MoveWindow(hSecondWnd, first + _Width, 0, second, cy, TRUE);
}

void HSplitter::onLButtonDown(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	SetCapture(hWnd);
	_OldPos = -1;
}

void HSplitter::onLButtonUp(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetCapture() != hWnd)
	{
		return;
	}

	ReleaseCapture();

	if (_OldPos > 0)
	{
		Draw(hWnd, _OldPos);
	}

	SendMessage(hWnd, WM_SIZE, 0, 0);
}

void HSplitter::onMouseMove(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetCapture() != hWnd)
	{
		return;
	}


	RECT rect;
	GetClientRect(hWnd, &rect);


	const int posValue = GET_X_LPARAM(lParam);
	const int maxValue = rect.right;
	_Percent = static_cast<double>(posValue) / static_cast<double>(maxValue);


	if (_Percent < 0.1)
	{
		_Percent = 0.1;
	}
	else if (_Percent > 0.9)
	{
		_Percent = 0.9;
	}


	const int curValue = static_cast<int>(maxValue * _Percent);
	if (_OldPos != curValue)
	{
		if (_OldPos > 0)
		{
			Draw(hWnd, _OldPos);
		}

		Draw(hWnd, curValue);
		_OldPos = curValue;
	}


	SendMessage(hWnd, WM_SIZE, 0, 0);
}





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
		_Splitter.UpdateLayout(_hWnd, _WidgetView->_hWnd, _LogView->_hWnd);
	}


	//-----------------------------------------------------------------------
	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	_Splitter.Draw(hWnd);
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
	LRESULT rv;


	rv = ::DefWindowProcW(hWnd, uMsg, wParam, lParam);

	//_Splitter.Draw(hWnd);

	return  rv;
#endif
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




