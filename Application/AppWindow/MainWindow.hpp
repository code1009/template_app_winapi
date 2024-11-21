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
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void registerWindowClass(void);

public:
	void createWindow(void);
	void destroyWindow(void);
};





