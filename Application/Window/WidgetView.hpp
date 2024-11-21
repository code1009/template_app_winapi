/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WidgetView : public mwa::Window
{
public:
	std::unique_ptr<widget::view_window> _Window;

public:
	explicit WidgetView(HWND hWndParent);

public:
	virtual ~WidgetView();

public:
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void createWindow(HWND hWndParent);
	void destroyWindow(void);

public:
	LRESULT onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnHScroll(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnVScroll(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnMouseWheel(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	
	LRESULT OnMouseMove(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

public:
	void onIdle(void);
};





