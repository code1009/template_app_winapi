////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "Direct2D.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma comment (lib, "D2d1.lib")





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
ID2D1Factory* Direct2D::_Factory = nullptr;

//==============================================================================
bool Direct2D::newFactory(void)
{
	HRESULT hr;


	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_Factory);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void Direct2D::deleteFactory(void)
{
	if (_Factory)
	{
		_Factory->Release();
		_Factory = nullptr;
	}
}





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
Direct2D::Direct2D()
{
}

//==============================================================================
Direct2D::~Direct2D()
{
	destroyDeviceResources();
}

//==============================================================================
bool Direct2D::createDeviceResources(HWND hWnd)
{
	HRESULT hr = S_OK;

	if (!_RenderTarget)
	{
		//--------------------------------------------------------------------------
		RECT rect;

		GetClientRect(hWnd, &rect);


		D2D1_SIZE_U size = D2D1::SizeU(
			rect.right - rect.left,
			rect.bottom - rect.top
		);


		// Create a Direct2D render target.
		hr = _Factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&_RenderTarget
		);

		if (SUCCEEDED(hr))
		{
			// Create a gray brush.
			hr = _RenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
				&_LightSlateGrayBrush
			);
		}
		if (SUCCEEDED(hr))
		{
			// Create a blue brush.
			hr = _RenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
				&_CornflowerBlueBrush
			);
		}
	}


	return true;
}

void Direct2D::destroyDeviceResources(void)
{
	if (_RenderTarget)
	{
		_RenderTarget->Release();
		_RenderTarget = nullptr;
	}

	if (_LightSlateGrayBrush)
	{
		_LightSlateGrayBrush->Release();
		_LightSlateGrayBrush = nullptr;
	}

	if (_CornflowerBlueBrush)
	{
		_CornflowerBlueBrush->Release();
		_CornflowerBlueBrush = nullptr;
	}
}

void Direct2D::resize(HWND hWnd, UINT width, UINT height)
{
	if (_RenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.

		_RenderTarget->Resize(D2D1::SizeU(width, height));
	}
}

void Direct2D::render(HWND hWnd)
{
	HRESULT hr; 
	
	
	hr = createDeviceResources(hWnd);
	if (SUCCEEDED(hr))
	{
		_RenderTarget->BeginDraw();
		
		on_render();

		hr = _RenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
	{
		destroyDeviceResources();
	}
}

void Direct2D::on_render(void)
{
	float zoom = 1;


	_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));


	D2D1_SIZE_F rtSize = _RenderTarget->GetSize();
	float width = rtSize.width;
	float height = rtSize.height;


	// Draw horizontal lines
	for (float x = 0.0f; x < width; x += 16.0f * zoom)
	{
		_RenderTarget->DrawLine(
			D2D1::Point2F(x, 0.0f),
			D2D1::Point2F(x, height),
			_LightSlateGrayBrush,
			zoom
		);
	}

	// Draw vertical lines
	for (float y = 0.0f; y < height; y += 16.0f * zoom)
	{
		_RenderTarget->DrawLine(
			D2D1::Point2F(0.0f, y),
			D2D1::Point2F(width, y),
			_LightSlateGrayBrush,
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
	_RenderTarget->FillRectangle(&rectangle1, _LightSlateGrayBrush);

	// Draw the outline of a rectangle.
	_RenderTarget->DrawRectangle(&rectangle2, _CornflowerBlueBrush, 4 * zoom);
}
