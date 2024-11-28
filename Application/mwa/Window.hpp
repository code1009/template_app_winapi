/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr DWORD FrameWindowStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD FrameWindowStyleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

constexpr DWORD ControlWindowStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD ControlWindowStyleEx = 0;

constexpr DWORD MDIChildWindowStyle = WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD MDIChildWindowStyleEx = WS_EX_MDICHILD;

constexpr DWORD DialogWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
constexpr DWORD DialogWindowStyleEx = 0;

constexpr DWORD ToolWindowStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD ToolWindowStyleEx = WS_EX_TOOLWINDOW;

constexpr DWORD PopupWindowStyle = WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD PopupWindowStyleEx = 0;

constexpr DWORD ChildWindowStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
constexpr DWORD ChildWindowStyleEx = 0;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Window
{
public:
	HWND _hWnd{ nullptr };

public:
	Window() = default;

public:
	virtual ~Window() = default;

public:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

public:
	virtual LRESULT onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT __stdcall WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




