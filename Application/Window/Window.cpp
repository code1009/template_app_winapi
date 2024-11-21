////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "Application.hpp"
#include "WindowClass.hpp"
#include "Window.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
LRESULT __stdcall WindowProc(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCCREATE == uMsg)
	{
		auto userData = reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams;
		::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));

		(reinterpret_cast<Window*>(userData))->_hWnd = hWnd;
	}


	auto windowPtr = reinterpret_cast<Window*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));
	if (windowPtr)
	{
		LRESULT lResult { 0 };


		lResult = windowPtr->onMsg(hWnd, uMsg, wParam, lParam);


		if (WM_NCDESTROY == uMsg)
		{
			::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
			
			//windowPtr->_hWnd = nullptr;
		}


		return lResult;
	}


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
Window::Window()
{
}

//==============================================================================
Window::~Window()
{
}

//==============================================================================
void Window::registerWindowClass(void)
{
	WindowClass windowClass;


	windowClass.registerWindowClass();
}

void Window::createWindow(void)
{
	constexpr DWORD FrameWindowStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	constexpr DWORD FrameWindowStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;


	HWND hWndParent = nullptr;
	LPCWSTR lpszClassName = L"Window";
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

void Window::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}

	_hWnd = nullptr;
}

LRESULT Window::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}