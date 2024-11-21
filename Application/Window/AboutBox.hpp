/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutBox : public mwa::Window
{
public:
	AboutBox() = default;

public:
	virtual ~AboutBox() = default;

public:
	virtual LRESULT onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	INT_PTR doModal(HWND hWndParent);

public:
	LRESULT onInitDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void onCommand_OK(void);
	void onCommand_Cancel(void);
	void setInformation(void);
};





