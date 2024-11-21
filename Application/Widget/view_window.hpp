/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace widget
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class view_window : public mwa::dx2d_window
{
	//-----------------------------------------------------------------------
public:
	std::chrono::time_point<std::chrono::steady_clock> _last_draw_time;
	std::int64_t                                       _frame_draw_count{ 0 };
	float                                              _fps{ 0.0f };

public:
	std::int64_t _mouse_x{ 0 };
	std::int64_t _mouse_y{ 0 };

public:
	//IDWriteTextLayout*    _pStatusTextLayout{ nullptr };
	IDWriteTextFormat*    _pStatusTextFormat{ nullptr };
	ID2D1SolidColorBrush* _pStatusTextBrush{ nullptr };
	ID2D1SolidColorBrush* _pStatusBoxFillBrush{ nullptr };
	ID2D1SolidColorBrush* _pStatusBoxLineBrush{ nullptr };

public:
	ID2D1SolidColorBrush* _pDocumentGridLine0Brush{ nullptr };
	ID2D1SolidColorBrush* _pDocumentGridLine1Brush{ nullptr };
	ID2D1SolidColorBrush* _pDocumentGridLine2Brush{ nullptr };


	//-----------------------------------------------------------------------
public:
	ID2D1SolidColorBrush* _pLightSlateGrayBrush{ nullptr };
	ID2D1SolidColorBrush* _pCornflowerBlueBrush{ nullptr };
	ID2D1StrokeStyle* _pStrokeStyle{ nullptr };


	//-----------------------------------------------------------------------
public:
	explicit view_window(HWND hWnd);

public:
	virtual ~view_window();

protected:
	virtual bool create_device_resources(HWND hWnd) override;
	virtual void destroy_device_resources(void) override;

protected:
	virtual void draw(void) override;

protected:
	void calculate_fps(void);
	void draw_status(void);
	void draw_document_grid(void);
	void draw_document(void);

public:
	void set_mouse_position(std::int64_t mouse_x, std::int64_t mouse_y);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




