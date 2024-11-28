/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class LogListViewCtrl : public mwa::Window
{
private:
	WNDPROC _PrevWindowProc;

public:
	explicit LogListViewCtrl(HWND hWndParent);

public:
	virtual ~LogListViewCtrl() = default;

public:
	virtual LRESULT onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void createWindow(HWND hWndParent);
	void destroyWindow(void);

public:
	LRESULT onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnNotifyReflect(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnLvnGetDispInfo(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnNmCustomDraw(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPrePaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPostPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPreErase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPostErase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnItemPrePaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnItemPostPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnItemPreErase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnItemPostErase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSubItemPrePaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void initialize(void);
	void initializeColumn(void);
	void initializeItems(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class LogView : public mwa::Window
{
public:
	std::unique_ptr<LogListViewCtrl> _Control;

public:
	explicit LogView(HWND hWndParent);
	virtual ~LogView() = default;

public:
	virtual LRESULT onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void createWindow(HWND hWndParent);
	void destroyWindow(void);

public:
	LRESULT onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onNotify(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};





