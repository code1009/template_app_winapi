////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#pragma once





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
class AboutBox : public Window
{
public:
	AboutBox();
	virtual ~AboutBox();

public:
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam) override;

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
	void setInformation(void);
};





