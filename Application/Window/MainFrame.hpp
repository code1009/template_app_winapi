/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public mwa::Window
{
public:
	std::unique_ptr<WidgetView> _WidgetView;
	std::unique_ptr<LogView> _LogView;
	mwa::VSplitter _Splitter;

	std::unique_ptr<WidgetToolFrame> _WidgetToolFrame;
	std::unique_ptr<PropertyBox> _PropertyBox;

public:
	MainFrame();

public:
	virtual ~MainFrame() = default;

public:
	virtual LRESULT onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void createWindow(void);
	void destroyWindow(void);

public:
	LRESULT onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onCommand_App_About(void);
	void onCommand_App_Exit(void);
	LRESULT onNotify(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT onTimer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT onUser0(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void onIdle(void);
};





