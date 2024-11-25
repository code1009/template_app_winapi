/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "../Window/Direct2D.hpp"
#include "../Resource/Resource.h"
#include "WidgetViewRender.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WidgetViewRender::WidgetViewRender()
{
	_LastTime = std::chrono::steady_clock::now();
}

//===========================================================================
WidgetViewRender::~WidgetViewRender()
{
	destroyDeviceResources();
}

//===========================================================================
bool WidgetViewRender::createDeviceResources(HWND hWnd)
{
	//-----------------------------------------------------------------------
	if (!Direct2D::createDeviceResources(hWnd))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	HRESULT hr; 
	
	
	//-----------------------------------------------------------------------
	if (!_pTextBrush)
	{
		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&_pTextBrush
		);
		if (FAILED(hr))
		{
			destroyDeviceResources();
			return false;
		}
	}

	if (!_pTextFormat)
	{
		hr = _pDWriteFactory->CreateTextFormat(
			//L"Arial",
			L"돋움",
			//L"FixedSys",
			nullptr,
			DWRITE_FONT_WEIGHT_ULTRA_BLACK, // DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			16.0f,
			//L"en-us",
			L"ko-kr",
			&_pTextFormat
		);
		if (FAILED(hr))
		{
			destroyDeviceResources();
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
			destroyDeviceResources();
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
			destroyDeviceResources();
			return false;
		}
	}


	return true;
}

void WidgetViewRender::destroyDeviceResources(void)
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


	//-----------------------------------------------------------------------
	if (_pTextBrush)
	{
		_pTextBrush->Release();
		_pTextBrush = nullptr;
	}

	if (_pTextFormat)
	{
		_pTextFormat->Release();
		_pTextFormat = nullptr;
	}


	//-----------------------------------------------------------------------
	Direct2D::destroyDeviceResources();
}

//===========================================================================
void WidgetViewRender::on_render(void)
{
	calculateFPS();

	_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	drawContents();

	drawStatus();
}

//===========================================================================
void WidgetViewRender::calculateFPS(void)
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = currentTime - _LastTime;
	_FrameCount++;


	if (elapsed.count() >= 1.0f)
	{
		_Fps = _FrameCount / elapsed.count();
		_FrameCount = 0;
		_LastTime = currentTime;
	}
}

void WidgetViewRender::drawStatus(void)
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


	swprintf_s(frameText, L"%03d frame",
		static_cast<int>(_FrameCount)
	);


	//-----------------------------------------------------------------------
	wchar_t fpsText[256];


	swprintf_s(fpsText, L"%03d fps",
		static_cast<int>(_Fps)
	);


	//-----------------------------------------------------------------------
	std::wstring text;


	text  = timeText ; text += L"\n";
	text += frameText; text += L"\n";
	text += fpsText  ; text += L"\n";


	_pRenderTarget->DrawTextW(
		text.c_str(),
		static_cast<UINT32>(text.length()),
		_pTextFormat,
		D2D1::RectF(0, 0, 400, 200),
		_pTextBrush
	);
}

//===========================================================================
void WidgetViewRender::drawContents(void)
{
	float zoom = 1;


	D2D1_SIZE_F rtSize = _pRenderTarget->GetSize();

	float width  = rtSize.width;
	float height = rtSize.height;


	// Draw horizontal lines
	for (float x = 0.0f; x < width; x += 16.0f * zoom)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(x, 0.0f),
			D2D1::Point2F(x, height),
			_pLightSlateGrayBrush,
			zoom
		);
	}

	// Draw vertical lines
	for (float y = 0.0f; y < height; y += 16.0f * zoom)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, y),
			D2D1::Point2F(width, y),
			_pLightSlateGrayBrush,
			zoom
		);
	}

	// Draw two rectangles.
	D2D1_RECT_F rectangle1 = D2D1::RectF(
		rtSize.width / (2.0f) - 40.0f * zoom,
		rtSize.height / (2.0f) - 40.0f * zoom,
		rtSize.width / (2.0f) + 40.0f * zoom,
		rtSize.height / (2.0f) + 40.0f * zoom
	);

	D2D1_RECT_F rectangle2 = D2D1::RectF(
		rtSize.width / (2.0f) - 80.0f * zoom,
		rtSize.height / (2.0f) - 80.0f * zoom,
		rtSize.width / (2.0f) + 80.0f * zoom,
		rtSize.height / (2.0f) + 80.0f * zoom
	);

	// Draw a filled rectangle.
	_pRenderTarget->FillRectangle(&rectangle1, _pLightSlateGrayBrush);

	// Draw the outline of a rectangle.
	_pRenderTarget->DrawRectangle(&rectangle2, _pCornflowerBlueBrush, 4 * zoom);
}




