////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "../Resource/Resource.h"
#include "MainFrame.hpp"
#include "AboutBox.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
constexpr LPCWSTR MainFrame_ClassName = L"xMainFrame";





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
MainFrame::MainFrame()
{
	WindowClass windowClass;


	windowClass.registerWindowClass(
		MainFrame_ClassName, 
		IDC_MAINFRAME, 
		IDI_MAINFRAME, IDI_SMALL
	);


	createWindow();

	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);
}

//==============================================================================
MainFrame::~MainFrame()
{
}

//==============================================================================
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
	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//==============================================================================
void MainFrame::createWindow(void)
{
	constexpr DWORD FrameWindowStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	constexpr DWORD FrameWindowStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;


	HWND    hWndParent    = nullptr;
	LPCWSTR lpszClassName = MainFrame_ClassName;
	LPCWSTR lpWindowName  = L"Window";
	DWORD   dwStyle       = FrameWindowStyle;
	DWORD   dwExStyle     = FrameWindowStyleEx;
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

//==============================================================================
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

LRESULT MainFrame::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//return 1;
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainFrame::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 10, 10, L"MainFrame", 9);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
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

//==============================================================================
void MainFrame::onIdle(void)
{
//	OutputDebugStringW(L"MainFrame::onIdle()\r\n");
//	Sleep(10);
}
