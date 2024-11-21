////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#pragma once





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
class MainWindow : public Window
{
public:
	MainWindow();
	virtual ~MainWindow();

public:
	virtual void registerWindowClass(void) override;

public:
	virtual void createWindow(void) override;

public:
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam) override;
};





