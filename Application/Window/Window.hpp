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
	virtual void registerWindowClass(void);

public:
	virtual void createWindow(void);
	virtual void destroyWindow(void);

public:
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
};





