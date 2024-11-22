/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WidgetViewRender : public Direct2D
{
public:
	ID2D1SolidColorBrush* _pLightSlateGrayBrush{ nullptr };
	ID2D1SolidColorBrush* _pCornflowerBlueBrush{ nullptr };
	
	IDWriteTextFormat*    _pTextFormat{ nullptr };
	IDWriteTextLayout*    _pTextLayout{ nullptr };
	ID2D1SolidColorBrush* _pTextBrush { nullptr };

	std::chrono::time_point<std::chrono::steady_clock> _lastTime;
	std::int64_t                                       _frameCount{ 0 };
	float                                              _fps{ 0.0f };

public:
	WidgetViewRender();

public:
	virtual ~WidgetViewRender();

protected:
	virtual bool createDeviceResources(HWND hWnd) override;
	virtual void destroyDeviceResources(void) override;

public:
	virtual void on_render(void) override;

public:
	void calculateFPS(void);
	void drawStatus(void);
	void drawContents(void);
};
