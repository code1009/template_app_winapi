////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "MainWindow.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
constexpr LPCWSTR MainWindow_ClassName = L"MainWindow";





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
MainWindow::MainWindow()
{
}

//==============================================================================
MainWindow::~MainWindow()
{
}

//==============================================================================
LRESULT MainWindow::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

//==============================================================================
void MainWindow::registerWindowClass(void)
{
	WindowClass windowClass;


	windowClass.registerWindowClass(MainWindow_ClassName, 0);
}

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
}

void MainWindow::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}

	_hWnd = nullptr;
}
