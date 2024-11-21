/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../mwa/RuntimeDebug.hpp"
#include "../mwa/Application.hpp"
#include "../mwa/WindowClass.hpp"
#include "../mwa/Window.hpp"
#include "../mwa/dx2d.hpp"

#include "view_window.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace widget
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
view_window::view_window(HWND hWnd) :
	mwa::dx2d_window(hWnd)
{
	_last_draw_time = std::chrono::steady_clock::now();

	set_window_size(0, 0);
	set_document_size(1920, 1080);
	enable_scrollbar(true);
}

//===========================================================================
view_window::~view_window()
{
	destroy_device_resources();
}

//===========================================================================
bool view_window::create_device_resources(HWND hWnd)
{
	//-----------------------------------------------------------------------
	if (!dx2d::create_device_resources(hWnd))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	HRESULT hr; 
	
	
	//-----------------------------------------------------------------------
	if (!_pStatusBoxFillBrush)
	{
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(0.9f, 0.9f, 0.9f, 0.5f),
			&_pStatusBoxFillBrush
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}
	if (!_pStatusBoxLineBrush)
	{
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(0.5f, 0.5f, 0.5f, 0.5f),
			&_pStatusBoxLineBrush
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}
	if (!_pStatusTextBrush)
	{
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(0.2f, 0.2f, 0.5f, 0.9f),
			&_pStatusTextBrush
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}
	if (!_pStatusTextFormat)
	{
		hr = _pDWriteFactory->CreateTextFormat(
			//L"Arial",
			L"돋움",
			//L"FixedSys",
			nullptr,
			DWRITE_FONT_WEIGHT_ULTRA_BLACK, // DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			12.0f,
			//L"en-us",
			L"ko-kr",
			&_pStatusTextFormat
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
		//_pStatusTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		_pStatusTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER); // vcenter
	}


	//-----------------------------------------------------------------------
	if (!_pDocumentGridLine0Brush)
	{
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(0.9f, 0.9f, 0.9f),
			&_pDocumentGridLine0Brush
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}
	if (!_pDocumentGridLine1Brush)
	{
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(0.5f, 0.5f, 0.5f),
			&_pDocumentGridLine1Brush
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}
	if (!_pDocumentGridLine2Brush)
	{
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(0.5f, 0.5f, 1.0f),
			&_pDocumentGridLine2Brush
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}


	//-----------------------------------------------------------------------
	if (!_pLightSlateGrayBrush)
	{
		// Create a gray brush.
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::LightSlateGray),
			&_pLightSlateGrayBrush
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}
	if (!_pCornflowerBlueBrush)
	{
		// Create a blue brush.
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
			&_pCornflowerBlueBrush
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}
	if (!_pStrokeStyle)
	{
		hr = _pFactory->CreateStrokeStyle(
			D2D1::StrokeStyleProperties(
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_LINE_JOIN_ROUND
			),
			nullptr,
			0,
			&_pStrokeStyle
		);
		if (FAILED(hr))
		{
			destroy_device_resources();
			return false;
		}
	}

	return true;
}

void view_window::destroy_device_resources(void)
{
	//-----------------------------------------------------------------------
	if (_pLightSlateGrayBrush)
	{
		_pLightSlateGrayBrush->Release();
		_pLightSlateGrayBrush = nullptr;
	}
	if (_pCornflowerBlueBrush)
	{
		_pCornflowerBlueBrush->Release();
		_pCornflowerBlueBrush = nullptr;
	}
	if (_pStrokeStyle)
	{
		_pStrokeStyle->Release();
		_pStrokeStyle = nullptr;
	}


	//-----------------------------------------------------------------------
	if (_pDocumentGridLine0Brush)
	{
		_pDocumentGridLine0Brush->Release();
		_pDocumentGridLine0Brush = nullptr;
	}
	if (_pDocumentGridLine1Brush)
	{
		_pDocumentGridLine1Brush->Release();
		_pDocumentGridLine1Brush = nullptr;
	}
	if (_pDocumentGridLine2Brush)
	{
		_pDocumentGridLine2Brush->Release();
		_pDocumentGridLine2Brush = nullptr;
	}


	//-----------------------------------------------------------------------
	if (_pStatusBoxFillBrush)
	{
		_pStatusBoxFillBrush->Release();
		_pStatusBoxFillBrush = nullptr;
	}
	if (_pStatusBoxLineBrush)
	{
		_pStatusBoxLineBrush->Release();
		_pStatusBoxLineBrush = nullptr;
	}
	if (_pStatusTextBrush)
	{
		_pStatusTextBrush->Release();
		_pStatusTextBrush = nullptr;
	}
	if (_pStatusTextFormat)
	{
		_pStatusTextFormat->Release();
		_pStatusTextFormat = nullptr;
	}


	//-----------------------------------------------------------------------
	dx2d::destroy_device_resources();
}

//===========================================================================
void view_window::draw(void)
{
	//-----------------------------------------------------------------------
	calculate_fps();


	//-----------------------------------------------------------------------
	D2D1::Matrix3x2F matrix;


	matrix = D2D1::Matrix3x2F::Identity();
	//_pRenderTarget->GetTransform(&matrix);


	//-----------------------------------------------------------------------
	matrix =
		D2D1::Matrix3x2F::Scale(
			static_cast<FLOAT>(_scale), 
			static_cast<FLOAT>(_scale)
		);
	matrix =
		matrix *
		D2D1::Matrix3x2F::Translation(
			static_cast<FLOAT>(-_document_viewport_x), 
			static_cast<FLOAT>(-_document_viewport_y)
		);
	_pRenderTarget->SetTransform(matrix);
	

	//-----------------------------------------------------------------------
	_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));


	//-----------------------------------------------------------------------
	draw_document_grid();
	draw_document();


	//-----------------------------------------------------------------------
	matrix = D2D1::Matrix3x2F::Identity();
	_pRenderTarget->SetTransform(matrix);

	draw_status();
}

//===========================================================================
void view_window::calculate_fps(void)
{
	_frame_draw_count++;


	auto current_draw_time = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = current_draw_time - _last_draw_time;


	if (elapsed.count() >= 1.0f)
	{
		_fps = _frame_draw_count / elapsed.count();
		_frame_draw_count = 0;
		_last_draw_time = current_draw_time;
	}
}

void view_window::draw_status(void)
{
	//-----------------------------------------------------------------------
	SYSTEMTIME st;


	GetLocalTime(&st);


	//-----------------------------------------------------------------------
	wchar_t timeText[256];


	swprintf_s(timeText, L"%02d:%02d:%02d.%03d",
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds
	);


	//-----------------------------------------------------------------------
	wchar_t frameText[256];


	swprintf_s(frameText, L"%03d 프레임",
		static_cast<int>(_frame_draw_count)
	);


	//-----------------------------------------------------------------------
	wchar_t fpsText[256];


	swprintf_s(fpsText, L"%03d FPS",
		static_cast<int>(_fps)
	);


	//-----------------------------------------------------------------------
	wchar_t scaleText[256];


	swprintf_s(scaleText, L"배율: %.2f",
		_scale
	);


	//-----------------------------------------------------------------------
	double _document_mouse_x;
	double _document_mouse_y;

	window_to_document(_mouse_x, _mouse_y, _document_mouse_x, _document_mouse_y);


	wchar_t mouseText[256];


	swprintf_s(mouseText, L"마우스: (%d-%d) (%.0f-%.0f)",
		static_cast<int>(_mouse_x),
		static_cast<int>(_mouse_y),
		_document_mouse_x,
		_document_mouse_y
	);


	//-----------------------------------------------------------------------
	std::wstring text;


	text  = timeText ; text += L"\n";
	text += frameText; text += L"\n";
	text += fpsText; text += L"\n";
	text += scaleText; text += L"\n";
	text += mouseText; text += L"\n";


	//-----------------------------------------------------------------------
	D2D1_SIZE_F size = _pRenderTarget->GetSize();


	float width  = size.width;
	float height = size.height;
	float space = 10.0f;

	float cx = 310;
	float cy = 135;


	D2D1_RECT_F rect;


	rect.left   = (width  > cx) ? width -cx : 0.0f;
	rect.right  = width;
#if 0
	// right / bottom
	rect.top    = (height > cy) ? height-cy : 0.0f;
	rect.bottom = height;
#else
	// right / top
	rect.top    = 0.0f;
	rect.bottom = cy;
#endif

	rect.left   += 20.0f;
	rect.top    += 20.0f;
	rect.right  -= 20.0f;
	rect.bottom -= 20.0f;
#if 0
	_pRenderTarget->FillRectangle(
		&rect,
		_pStatusBoxFillBrush
	);
#else
	D2D1_ROUNDED_RECT rrect;
	

	rrect.rect.left   = rect.left  ;
	rrect.rect.top    = rect.top   ;
	rrect.rect.right  = rect.right ;
	rrect.rect.bottom = rect.bottom;
	rrect.radiusX = 5.0f;
	rrect.radiusY = 5.0f;
	_pRenderTarget->FillRoundedRectangle(&rrect, _pStatusBoxFillBrush);
	_pRenderTarget->DrawRoundedRectangle(&rrect, _pStatusBoxLineBrush);
#endif

	rect.left   += 10.0f;
	rect.top    += 10.0f;
	rect.right  -= 10.0f;
	rect.bottom -= 10.0f;
	_pRenderTarget->DrawTextW(
		text.c_str(),
		static_cast<UINT32>(text.length()),
		_pStatusTextFormat,
		rect,
		_pStatusTextBrush
	);
}

//===========================================================================
void view_window::draw_document_grid(void)
{
	//-----------------------------------------------------------------------
	double document_cx;
	double document_cy;


	get_document_size(document_cx, document_cy);


	//-----------------------------------------------------------------------
	double viewport_x;
	double viewport_y;
	double viewport_cx;
	double viewport_cy;


	get_document_viewport_point(viewport_x, viewport_y);
	get_document_viewport_size(viewport_cx, viewport_cy);


	//-----------------------------------------------------------------------
	float ob;
	float oe;
	float cb;
	float ce;
	float ci;
	float cd;


	//-----------------------------------------------------------------------
	// Draw horizontal lines
	cd = static_cast<float>(20.0f);
	cb = static_cast<float>(0.0f);
	ce = static_cast<float>(document_cx);
	ob = static_cast<float>(0.0f);
	oe = static_cast<float>(document_cy);
	for (ci = cb; ci < ce; ci += cd)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(ci, ob),
			D2D1::Point2F(ci, oe),
			_pDocumentGridLine0Brush,
			1.0f
		);
	}
	// Draw vertical lines
	cd = static_cast<float>(20.0f);
	cb = static_cast<float>(0.0f);
	ce = static_cast<float>(document_cy);
	ob = static_cast<float>(0.0f);
	oe = static_cast<float>(document_cx);
	for (ci = cb; ci < ce; ci += cd)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(ob, ci),
			D2D1::Point2F(oe, ci),
			_pDocumentGridLine0Brush,
			1.0f
		);
	}

	// Draw horizontal lines
	cd = static_cast<float>(100.0f);
	cb = static_cast<float>(0.0f);
	ce = static_cast<float>(document_cx);
	ob = static_cast<float>(0.0f);
	oe = static_cast<float>(document_cy);
	for (ci = cb; ci < ce; ci += cd)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(ci, ob),
			D2D1::Point2F(ci, oe),
			_pDocumentGridLine1Brush,
			1.0f
		);
	}
	// Draw vertical lines
	cd = static_cast<float>(100.0f);
	cb = static_cast<float>(0.0f);
	ce = static_cast<float>(document_cy);
	ob = static_cast<float>(0.0f);
	oe = static_cast<float>(document_cx);
	for (ci = cb; ci < ce; ci += cd)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(ob, ci),
			D2D1::Point2F(oe, ci),
			_pDocumentGridLine1Brush,
			1.0f
		);
	}


	//-----------------------------------------------------------------------
	// Draw center lines
	cb = static_cast<float>(0.0f);
	ce = static_cast<float>(document_cx);
	ob = static_cast<float>(0.0f);
	oe = static_cast<float>(document_cy);
	ci = (ce - cb) / 2.0f;
	_pRenderTarget->DrawLine(
		D2D1::Point2F(ci, ob),
		D2D1::Point2F(ci, oe),
		_pDocumentGridLine2Brush,
		2.0f
	);

	cb = static_cast<float>(0.0f);
	ce = static_cast<float>(document_cy);
	ob = static_cast<float>(0.0f);
	oe = static_cast<float>(document_cx);
	ci = (ce - cb) / 2.0f;
	_pRenderTarget->DrawLine(
		D2D1::Point2F(ob, ci),
		D2D1::Point2F(oe, ci),
		_pDocumentGridLine2Brush,
		2.0f
	);


	//-----------------------------------------------------------------------
	// Draw the outline of a rectangle.
	D2D1_RECT_F rect;


	rect.left   = static_cast<float>(0.0f);
	rect.top    = static_cast<float>(0.0f);
	rect.right  = static_cast<float>(document_cx);
	rect.bottom = static_cast<float>(document_cy);
	_pRenderTarget->DrawRectangle(
		&rect,
		_pDocumentGridLine2Brush,
		4.0f
	);
}

void view_window::set_mouse_position(std::int64_t mouse_x, std::int64_t mouse_y)
{
	_mouse_x = mouse_x;
	_mouse_y = mouse_y;
}

//===========================================================================
void view_window::draw_document(void)
{
	//-----------------------------------------------------------------------
	D2D1_SIZE_F size{ 1000.0f, 1000.0f };


	_pRenderTarget->DrawLine(
		D2D1::Point2F(0.0f, 0.0f),
		D2D1::Point2F(1000.0f, 1000.0f),
		_pLightSlateGrayBrush,
		1.0f
	);

	// Draw two rectangles.
	D2D1_RECT_F rectangle1 = D2D1::RectF(
		size.width  / (2.0f) - 40.0f,
		size.height / (2.0f) - 40.0f,
		size.width  / (2.0f) + 40.0f,
		size.height / (2.0f) + 40.0f
	);

	D2D1_RECT_F rectangle2 = D2D1::RectF(
		size.width  / (2.0f) - 80.0f,
		size.height / (2.0f) - 80.0f,
		size.width  / (2.0f) + 80.0f,
		size.height / (2.0f) + 80.0f
	);

	// Draw a filled rectangle.
	_pRenderTarget->FillRectangle(&rectangle1, _pLightSlateGrayBrush);

	// Draw the outline of a rectangle.
	_pRenderTarget->DrawRectangle(&rectangle2, _pCornflowerBlueBrush, 4.0f);


	//-----------------------------------------------------------------------
#if 0
	ID2D1StrokeStyle* pStrokeStyle;
	//FLOAT dashes[] = { 2.0f, 2.0f };
	FLOAT dashes[] = { 0.0f };
	D2D1_STROKE_STYLE_PROPERTIES StrokeStyleProperties =
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_ROUND
		);

	_pFactory->CreateStrokeStyle(
		/*
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND,
			D2D1_CAP_STYLE_ROUND,
			D2D1_LINE_JOIN_ROUND,
			0.0f,
			D2D1_DASH_STYLE_CUSTOM,
			0.0f
		)
		*/
		StrokeStyleProperties
		,
		///dashes,
		//ARRAYSIZE(dashes),
		//sizeof(dashes)/sizeof(FLOAT),
		nullptr,
		0,
		&pStrokeStyle
	);
#endif

	_pRenderTarget->DrawLine(
		D2D1::Point2F(100.0f, 100.0f),
		D2D1::Point2F(300.0f, 100.0f),
		//_pDocumentGridLine1Brush,
		_pStatusBoxLineBrush,
		22.0f,
		_pStrokeStyle
	);
	_pRenderTarget->DrawLine(
		D2D1::Point2F(300.0f, 100.0f),
		D2D1::Point2F(400.0f, 200.0f),
		//_pDocumentGridLine1Brush,
		_pStatusBoxLineBrush,
		22.0f,
		_pStrokeStyle
	);

	_pRenderTarget->DrawLine(
		D2D1::Point2F(100.0f, 100.0f),
		D2D1::Point2F(300.0f, 100.0f),
		//_pDocumentGridLine0Brush,
		_pStatusBoxFillBrush,
		20.0f,
		_pStrokeStyle
	);
	_pRenderTarget->DrawLine(
		D2D1::Point2F(300.0f, 100.0f),
		D2D1::Point2F(400.0f, 200.0f),
		//_pDocumentGridLine0Brush,
		_pStatusBoxFillBrush,
		20.0f,
		_pStrokeStyle
	);

#if 0
	pStrokeStyle->Release();
	pStrokeStyle = nullptr;
#endif


	//-----------------------------------------------------------------------
	D2D1_RECT_F rect;
	std::wstring text { L"동해물과 백두산이 마르고 닳도록" };

	rect.left = 20.0f;
	rect.top = 40.0f;
	rect.right = 500.0f;
	rect.bottom = 80.0f;
	_pRenderTarget->DrawTextW(
		text.c_str(),
		static_cast<UINT32>(text.length()),
		_pStatusTextFormat,
		rect,
		_pStatusTextBrush
	); 
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




