/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "Direct2D.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma comment (lib, "D2d1.lib")
#pragma comment (lib, "Dwrite.lib")





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
ID2D1Factory* Direct2D::_pFactory = nullptr;
IDWriteFactory* Direct2D::_pDWriteFactory = nullptr;

//===========================================================================
bool Direct2D::newFactory(void)
{
	//-----------------------------------------------------------------------
	HRESULT hr;


	//-----------------------------------------------------------------------
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pFactory);
	if (FAILED(hr))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&_pDWriteFactory)
	);
	if (FAILED(hr))
	{
		deleteFactory();
		return false;
	}


	return true;
}

void Direct2D::deleteFactory(void)
{
	if (_pFactory)
	{
		_pFactory->Release();
		_pFactory = nullptr;
	}


	if (_pDWriteFactory)
	{
		_pDWriteFactory->Release();
		_pDWriteFactory = nullptr;
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Direct2D::Direct2D()
{
}

//===========================================================================
Direct2D::~Direct2D()
{
	destroyDeviceResources();
}

//===========================================================================
bool Direct2D::createDeviceResources(HWND hWnd)
{
	HRESULT hr = S_OK;


	if (!_pRenderTarget)
	{
		//-------------------------------------------------------------------
		RECT rect;


		GetClientRect(hWnd, &rect);


		//-------------------------------------------------------------------
		D2D1_SIZE_U size = D2D1::SizeU(
			rect.right - rect.left,
			rect.bottom - rect.top
		);


		// Create a Direct2D render target.
		hr = _pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&_pRenderTarget
		);
		if (FAILED(hr))
		{
			return false;
		}
	}


	return true;
}

void Direct2D::destroyDeviceResources(void)
{
	if (_pRenderTarget)
	{
		_pRenderTarget->Release();
		_pRenderTarget = nullptr;
	}
}

void Direct2D::resize(HWND hWnd, UINT width, UINT height)
{
	if (_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}

void Direct2D::render(HWND hWnd)
{
	HRESULT hr; 
	
	
	hr = createDeviceResources(hWnd);
	if (SUCCEEDED(hr))
	{
		_pRenderTarget->BeginDraw();
		
		on_render();

		hr = _pRenderTarget->EndDraw();
	}
	if (hr == D2DERR_RECREATE_TARGET)
	{
		destroyDeviceResources();
	}
}

void Direct2D::on_render(void)
{
}




