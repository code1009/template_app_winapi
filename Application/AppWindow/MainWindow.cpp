////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "../Resource/Resource.h"
#include "MainWindow.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
constexpr LPCWSTR MainWindow_ClassName = L"xMainWindow";





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
MainWindow::MainWindow()
{
	WindowClass windowClass;


	windowClass.registerWindowClass(MainWindow_ClassName, IDI_MAINWINDOW);


	createWindow();

	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);
}

//==============================================================================
MainWindow::~MainWindow()
{
}

//==============================================================================
LRESULT MainWindow::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:  return onCreate (hWnd, uMsg, wParam, lParam);
	case WM_DESTROY: return onDestroy(hWnd, uMsg, wParam, lParam);
	case WM_CLOSE:   return onClose  (hWnd, uMsg, wParam, lParam);
	case WM_SIZE:    return onSize   (hWnd, uMsg, wParam, lParam);
	case WM_PAINT:   return onPaint  (hWnd, uMsg, wParam, lParam);
	case WM_COMMAND: return onCommand(hWnd, uMsg, wParam, lParam);
	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//==============================================================================
void MainWindow::createWindow(void)
{
	constexpr DWORD FrameWindowStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	constexpr DWORD FrameWindowStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;


	HWND hWndParent = nullptr;
	LPCWSTR lpszClassName = MainWindow_ClassName;
	LPCWSTR lpWindowName = L"Window";
	DWORD dwStyle = FrameWindowStyle;
	DWORD dwExStyle = FrameWindowStyleEx;
	int X = CW_USEDEFAULT;
	int Y = CW_USEDEFAULT;
	int nWidth = CW_USEDEFAULT;
	int nHeight = CW_USEDEFAULT;
	HMENU hMenu = nullptr;


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
		throw std::runtime_error("MainWindow::createWindow() failed");
	}
}

void MainWindow::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}

	_hWnd = nullptr;
}

//==============================================================================
LRESULT MainWindow::onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainWindow::onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	::PostQuitMessage(0);

	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainWindow::onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//destroyWindow();

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainWindow::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainWindow::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	
	
	HDC hdc = BeginPaint(hWnd, &ps);
	
	EndPaint(hWnd, &ps);


	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT MainWindow::onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
