/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class PropertyBox : public mwa::Window
{
private:
	HWND _hWndParent{ nullptr };

public:
	explicit PropertyBox(HWND hWndParent);

public:
	virtual ~PropertyBox() = default;

public:
	virtual LRESULT onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void createWindow(HWND hWndParent);
	void destroyWindow(void);

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
};





