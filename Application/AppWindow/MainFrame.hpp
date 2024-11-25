/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class VSplitter
{
public:
	const int _Width{ 4 };
	COLORREF  _Color;

	double    _Percent;
	int       _OldPos;

public:
	VSplitter();

public:
	void Draw(HWND hWnd, int curPos);
	void UpdateLayout(HWND hWnd, HWND hFirstWnd, HWND hSecondWnd);

public:
	void onLButtonDown(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	void onLButtonUp(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	void onMouseMove(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class HSplitter
{
public:
	const int _Width{ 4 };
	COLORREF  _Color;

	double    _Percent;
	int       _OldPos;

public:
	HSplitter();

public:
	void Draw(HWND hWnd, int curPos);
	void UpdateLayout(HWND hWnd, HWND hFirstWnd, HWND hSecondWnd);

public:
	void onLButtonDown(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	void onLButtonUp(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	void onMouseMove(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public Window
{
public:
	std::unique_ptr<WidgetView> _WidgetView;
	std::unique_ptr<LogView> _LogView;
	VSplitter _Splitter;

public:
	MainFrame();

public:
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
	LRESULT onNotify(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

public:
	void onIdle(void);
};





