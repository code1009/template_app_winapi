/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "../Window/Direct2D.hpp"
#include "../Resource/Resource.h"
#include "View.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
ViewRender::ViewRender()
{
	_lastTime = std::chrono::steady_clock::now();
}

ViewRender::~ViewRender()
{
	destroyDeviceResources();
}

//===========================================================================
bool ViewRender::createDeviceResources(HWND hWnd)
{
	//-----------------------------------------------------------------------
	if (!Direct2D::createDeviceResources(hWnd))
	{
		return false;
	}


	//-----------------------------------------------------------------------
	HRESULT hr; 
	
	
	hr = S_OK;


	//-----------------------------------------------------------------------
	if (!_pTextBrush)
	{
		IDWriteFactory* pDWriteFactory = nullptr;


		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory)
		);
		if (FAILED(hr))
		{
			destroyDeviceResources();
			return false;
		}



		hr = _pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&_pTextBrush
		);
		if (FAILED(hr))
		{
			destroyDeviceResources();
			return false;
		}


		hr = pDWriteFactory->CreateTextFormat(
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


		pDWriteFactory->Release();
		pDWriteFactory = nullptr;
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

void ViewRender::destroyDeviceResources(void)
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

void ViewRender::calculateFPS(void)
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = currentTime - _lastTime;
	_frameCount++;


	if (elapsed.count() >= 1.0f)
	{
		_fps = _frameCount / elapsed.count();
		_frameCount = 0;
		_lastTime = currentTime;
	}
}

void ViewRender::on_render(void)
{
	calculateFPS();

	_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	drawContents();

	drawStatus();
}

void ViewRender::drawStatus(void)
{
	SYSTEMTIME st;


	GetLocalTime(&st);


	wchar_t timeText[256];


	swprintf_s(timeText, L"%02d:%02d:%02d.%03d",
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds
	);


	wchar_t frameText[256];


	swprintf_s(frameText, L"%03d frame",
		static_cast<int>(_frameCount)
	);


	wchar_t fpsText[256];


	swprintf_s(fpsText, L"%03d fps",
		static_cast<int>(_fps)
	);



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

void ViewRender::drawContents(void)
{
	float zoom = 1;


	D2D1_SIZE_F rtSize = _pRenderTarget->GetSize();
	float width = rtSize.width;
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




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR View_ClassName = L"xView";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
View::View(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	WindowClass windowClass;


	windowClass.registerWindowClass(
		View_ClassName
	);


	//-----------------------------------------------------------------------
	_ViewRender = std::make_unique<ViewRender>();


	//-----------------------------------------------------------------------
	createWindow(hWndParent);

	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);
}

//===========================================================================
View::~View()
{
}

//===========================================================================
LRESULT View::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:     return onCreate    (hWnd, uMsg, wParam, lParam);
	case WM_DESTROY:    return onDestroy   (hWnd, uMsg, wParam, lParam);
	case WM_CLOSE:      return onClose     (hWnd, uMsg, wParam, lParam);
	case WM_SIZE:       return onSize      (hWnd, uMsg, wParam, lParam);
	case WM_ERASEBKGND: return onEraseBkGnd(hWnd, uMsg, wParam, lParam);
	case WM_PAINT:      return onPaint     (hWnd, uMsg, wParam, lParam);
	case WM_COMMAND:    return onCommand   (hWnd, uMsg, wParam, lParam);
	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void View::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	//HWND    hWndParent    = nullptr;
	LPCWSTR lpszClassName = View_ClassName;
	LPCWSTR lpWindowName  = L"Window";
	DWORD   dwStyle       = ChildWindowStyle;
	DWORD   dwExStyle     = ChildWindowStyleEx;
	int     X             = CW_USEDEFAULT;
	int     Y             = CW_USEDEFAULT;
	int     nWidth        = CW_USEDEFAULT;
	int     nHeight       = CW_USEDEFAULT;
	HMENU   hMenu         = nullptr;


	//-----------------------------------------------------------------------
	HWND hWnd;


	hWnd = ::CreateWindowExW(
		dwExStyle,
		lpszClassName,
		lpWindowName,
		dwStyle,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		ApplicationGet()->_hInstance,
		this
	);

	if (nullptr==hWnd)
	{
		throw std::runtime_error("View::createWindow() failed");
	}
}

void View::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}

	_hWnd = nullptr;
}

//===========================================================================
LRESULT View::onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	SIZE size{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	UINT type{ (UINT)wParam };


	//-----------------------------------------------------------------------
	RECT rect;

	GetClientRect(hWnd, &rect);


	//-----------------------------------------------------------------------
	if (_ViewRender.get())
	{
		UINT cx;
		UINT cy;


		cx = static_cast<UINT>(rect.right  - rect.left);
		cy = static_cast<UINT>(rect.bottom - rect.top );

		_ViewRender->resize(_hWnd, cx, cy);
	}


	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//return TRUE;
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

#if 0
LRESULT View::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 0, 0, L"View", 4);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
#endif

LRESULT View::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	if (_ViewRender.get())
	{
		_ViewRender->render(_hWnd);
	}


	// The ValidateRect function validates the client area within a rectangle by
	// removing the rectangle from the update region of the window.
	::ValidateRect(_hWnd, nullptr);


	return 0;
	//return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT View::onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	int id = LOWORD(wParam);

	switch (id)
	{
	case IDM_APP_ABOUT:
		onCommand_App_About();
		return 0;

	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

void View::onCommand_App_About(void)
{
	MessageBoxW(
		_hWnd,
		L"App_About",
		L"App_About",
		MB_OK
	);
}

//===========================================================================
void View::onIdle(void)
{
	//OutputDebugStringW(L"View::onIdle()\r\n");
	//Sleep(10);

	if (_ViewRender.get())
	{
		_ViewRender->render(_hWnd);
	}
}
