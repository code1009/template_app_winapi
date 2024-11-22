/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public Window
{
public:
	std::unique_ptr<View> _View;
	std::unique_ptr<LogView> _LogView;

public:
	MainFrame();
	virtual ~MainFrame();

public:
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void createWindow(void);
	void destroyWindow(void);

public:
	LRESULT onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	void onCommand_App_About(void);
	void onCommand_App_Exit(void);

public:
	void onIdle(void);
};





