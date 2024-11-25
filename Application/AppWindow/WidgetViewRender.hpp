/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WidgetViewRender : public Direct2D
{
public:
	std::chrono::time_point<std::chrono::steady_clock> _LastTime;
	std::int64_t                                       _FrameCount{ 0 };
	float                                              _Fps{ 0.0f };

	IDWriteTextLayout* _pTextLayout{ nullptr };
	IDWriteTextFormat* _pTextFormat{ nullptr };
	ID2D1SolidColorBrush* _pTextBrush{ nullptr };

public:
	ID2D1SolidColorBrush* _pLightSlateGrayBrush{ nullptr };
	ID2D1SolidColorBrush* _pCornflowerBlueBrush{ nullptr };

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




