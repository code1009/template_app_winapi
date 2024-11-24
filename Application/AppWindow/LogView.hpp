﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class LogListViewCtrl : public Window
{
private:
	WNDPROC _ListViewWindowProc;

public:
	explicit LogListViewCtrl(HWND hWndParent);

public:
	virtual ~LogListViewCtrl();

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

	LRESULT OnNotifyReflect(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnLvnGetDispInfo(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnNmCustomDraw(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPrePaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPostPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPreErase(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnPostErase(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnItemPrePaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnItemPostPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnItemPreErase(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnItemPostErase(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSubItemPrePaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

public:
	void initialize(void);
	void initializeColumn(void);
	void initializeItems(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class LogView : public Window
{
public:
	std::unique_ptr<LogListViewCtrl> _LogListViewCtrl;

public:
	explicit LogView(HWND hWndParent);
	virtual ~LogView();

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
	LRESULT onNotify(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
};





