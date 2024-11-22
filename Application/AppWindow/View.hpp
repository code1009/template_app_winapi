/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class ViewRender : public Direct2D
{
public:
	ID2D1SolidColorBrush* _pLightSlateGrayBrush{ nullptr };
	ID2D1SolidColorBrush* _pCornflowerBlueBrush{ nullptr };
	
	IDWriteTextFormat* _pTextFormat{ nullptr };
	IDWriteTextLayout* _pTextLayout{ nullptr };
	ID2D1SolidColorBrush* _pTextBrush{ nullptr };

	std::chrono::time_point<std::chrono::steady_clock> _lastTime;
	std::int64_t _frameCount{ 0 };
	float _fps{ 0.0f };

public:
	ViewRender();
	virtual ~ViewRender();

protected:
	virtual bool createDeviceResources(HWND hWnd) override;
	virtual void destroyDeviceResources(void) override;

public:
	virtual void on_render(void) override;

public:
	void calculateFPS(void);
	void renderFPS(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class View : public Window
{
public:
	std::unique_ptr<ViewRender> _ViewRender;

public:
	explicit View(HWND hWndParent);
	virtual ~View();

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
	void onCommand_App_About(void);

public:
	void onIdle(void);
};





