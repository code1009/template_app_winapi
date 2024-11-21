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
	virtual ~PropertyBox();

public:
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void createWindow(HWND hWndParent);
	void destroyWindow(void);

public:
	LRESULT onInitDialog(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

public:
	void onCommand_OK(void);
	void onCommand_Cancel(void);
};





