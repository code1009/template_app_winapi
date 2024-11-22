////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#pragma once





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
class Window
{
public:
	HWND _hWnd{ nullptr };

public:
	Window();
	virtual ~Window();

public:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

public:
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
};





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
LRESULT __stdcall WindowProc(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall DialogProc(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

