/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "dx2d.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma comment (lib, "D2d1.lib")
#pragma comment (lib, "Dwrite.lib")





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
ID2D1Factory* dx2d::_pFactory = nullptr;
IDWriteFactory* dx2d::_pDWriteFactory = nullptr;

//===========================================================================
bool dx2d::new_factory(void)
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
		delete_factory();
		return false;
	}


	return true;
}

void dx2d::delete_factory(void)
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
dx2d::~dx2d()
{
	destroy_device_resources();
}

//===========================================================================
bool dx2d::create_device_resources(HWND hWnd)
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

#if 0
		constexpr int DEFAULT_DPI{ 96 };
		hr = _pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(),
				DEFAULT_DPI, DEFAULT_DPI,
				D2D1_RENDER_TARGET_USAGE_NONE,
				D2D1_FEATURE_LEVEL_DEFAULT
			),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&_pRenderTarget
		);
#else
		hr = _pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&_pRenderTarget
		);
#endif
		if (FAILED(hr))
		{
			return false;
		}
	}


	return true;
}

void dx2d::destroy_device_resources(void)
{
	if (_pRenderTarget)
	{
		_pRenderTarget->Release();
		_pRenderTarget = nullptr;
	}
}

void dx2d::resize(std::int64_t width, std::int64_t height)
{
	if (_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		_pRenderTarget->Resize(
			D2D1::SizeU(static_cast<UINT32>(width), static_cast<UINT32>(height))
		);
	}
}

void dx2d::render(HWND hWnd)
{
	bool rv;

	
	rv = create_device_resources(hWnd);
	if (rv)
	{
		_pRenderTarget->BeginDraw();
		
		draw();


		HRESULT hr;


		hr = _pRenderTarget->EndDraw();
		if (hr == D2DERR_RECREATE_TARGET)
		{
			destroy_device_resources();
		}
	}
}

void dx2d::draw(void)
{
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if  0
https://www.codeproject.com/Articles/1042516/Custom-Controls-in-Win-API-Scrolling

typedef struct tagSCROLLINFO {
	UINT cbSize;
	UINT fMask;
	int  nMin;
	int  nMax;
	UINT nPage;
	int  nPos;
	int  nTrackPos;
} SCROLLINFO, * LPSCROLLINFO;



https://www.catch22.net/tuts/win32/64bit-scrollbars/

void example(HWND hwnd)
{
	UINT64 max = 0xffffffffffffffff;
	UINT64 pos = 0x1234567812345678;

	SetScrollInfo64(hwnd, SB_VERT, SIF_ALL, max, pos, 15, TRUE);

	// when reacting to a WM_VSCROLL, with SB_THUMBTRACK/SB_THUMBPOS:
	pos = GetScrollPos64(hwnd, SB_VERT, SIF_TRACKPOS, max);
}

#endif

//===========================================================================
#define WIN16_SCROLLBAR_MAX 0x7fff
#define WIN32_SCROLLBAR_MAX 0x7fffffff

//===========================================================================
// Wrapper around SetScrollInfo, performs scaling to 
// allow massive 64bit scroll ranges
BOOL SetScrollInfo64(HWND hwnd,
	int nBar,
	UINT fMask,
	UINT64 nMax64,
	UINT64 nPos64,
	UINT64 nPage,
	BOOL fRedraw
)
{
	SCROLLINFO si = { static_cast<UINT>(sizeof(si)), fMask };

	// normal scroll range requires no adjustment
	if (nMax64 <= WIN32_SCROLLBAR_MAX)
	{
		si.nMin = (int)0;
		si.nMax = (int)nMax64;
		si.nPage = (int)nPage;
		si.nPos = (int)nPos64;
	}
	// scale the scrollrange down into allowed bounds
	else
	{
		si.nMin = (int)0;
		si.nMax = (int)WIN16_SCROLLBAR_MAX;
		si.nPage = (int)nPage;
		si.nPos = (int)(nPos64 / (nMax64 / WIN16_SCROLLBAR_MAX));
	}

	return SetScrollInfo(hwnd, nBar, &si, fRedraw);
}

UINT64 GetScrollPos64(HWND hwnd,
	int nBar,
	UINT fMask,
	UINT64 nMax64
)
{
	SCROLLINFO si = { static_cast<UINT>(sizeof(si)), fMask | SIF_PAGE };
	UINT64 nPos32;


	if (!GetScrollInfo(hwnd, nBar, &si))
	{
		return 0;
	}


	nPos32 = (fMask & SIF_TRACKPOS) ? si.nTrackPos : si.nPos;

	// special-case: scroll position at the very end
	if (nPos32 == WIN16_SCROLLBAR_MAX - si.nPage + 1)
	{
		return nMax64 - si.nPage + 1;
	}
	// normal scroll range requires no adjustment
	else if (nMax64 <= WIN32_SCROLLBAR_MAX)
	{
		return nPos32;
	}
	// adjust the scroll position to be relative to maximum value
	else
	{
		return nPos32 * (nMax64 / WIN16_SCROLLBAR_MAX);
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
dx2d_window::dx2d_window(HWND hWnd) :
	_hwnd{ hWnd }
{
}

//===========================================================================
void dx2d_window::get_window_size(std::int64_t& cx, std::int64_t& cy)
{
	cx = _window_cx;
	cy = _window_cy;
}

void dx2d_window::get_scale(double& scale)
{
	scale = _scale;
}

void dx2d_window::get_document_size(double& cx, double& cy)
{
	cx = _document_cx;
	cy = _document_cy;
}

void dx2d_window::get_document_viewport_point(double& x, double& y)
{
	x = _document_viewport_x;
	y = _document_viewport_y;
}

void dx2d_window::get_document_viewport_size(double& cx, double& cy)
{
	cx = _window_cx / _scale;
	cy = _window_cy / _scale;
}

void dx2d_window::get_image_size(std::int64_t& cx, std::int64_t& cy)
{
	cx = _image_cx;
	cy = _image_cy;
}

void dx2d_window::get_image_viewport_point(std::int64_t& x, std::int64_t& y)
{
	x = _image_viewport_x;
	y = _image_viewport_y;
}

void dx2d_window::get_image_viewport_size(std::int64_t& cx, std::int64_t& cy)
{
	cx = _window_cx;
	cy = _window_cy;
}

//===========================================================================
void dx2d_window::window_to_document(std::int64_t window_x, std::int64_t window_y, double& document_x, double& document_y)
{
	document_x = _document_viewport_x + (window_x / _scale);
	document_y = _document_viewport_y + (window_y / _scale);
}

void dx2d_window::document_to_window(double document_x, double document_y, std::int64_t& window_x, std::int64_t& window_y)
{
	window_x = static_cast<std::int64_t>((document_x - _document_viewport_x) * _scale);
	window_y = static_cast<std::int64_t>((document_y - _document_viewport_y) * _scale);
}

//===========================================================================
void dx2d_window::set_window_size(std::int64_t cx, std::int64_t cy)
{
	_window_cx = cx;
	_window_cy = cy;


	dx2d::resize(static_cast<UINT>(cx), static_cast<UINT>(cy));


	update_image_size();
	update_viewport();
	update_view_scroll();
	update_scrollbar_position();
}

void dx2d_window::set_scale(double scale)
{
	if (_scale > 0.0)
	{
		_scale = scale;

		update_image_size();
		update_viewport();
		update_view_scroll();
		update_scrollbar_position();

		repaint();
	}
}

void dx2d_window::set_document_size(double cx, double cy)
{
	_document_viewport_x = 0.0;
	_document_viewport_y = 0.0;
	_document_cx = cx;
	_document_cy = cy;

	update_image_size();
	update_viewport();
	update_view_scroll();
	update_scrollbar_position();

	repaint();
}

//===========================================================================
void dx2d_window::update_image_size(void)
{
	_image_cx = static_cast<std::int64_t>(_document_cx * _scale);
	_image_cy = static_cast<std::int64_t>(_document_cy * _scale);
}

void dx2d_window::update_viewport(void)
{
	//-----------------------------------------------------------------------
	// 변수명은 _window_cx이지만 _image_viewport_cx으로 해석 해야 함
	// _window_cx == _image_viewport_cx
	// _window_cy == _image_viewport_cy


	//-----------------------------------------------------------------------
	_image_viewport_x = static_cast<std::int64_t>(_document_viewport_x * _scale);
	if (_image_cx < _window_cx)
	{
		_image_viewport_x = 0;
	}
	else
	{
		if (_image_cx < (_image_viewport_x + _window_cx))
		{
			_image_viewport_x = _image_cx - _window_cx;
		}
	}


	//-----------------------------------------------------------------------
	_image_viewport_y = static_cast<std::int64_t>(_document_viewport_y * _scale);
	if (_image_cy < _window_cy)
	{
		_image_viewport_y = 0;
	}
	else
	{
		if (_image_cy < (_image_viewport_y + _window_cy))
		{
			_image_viewport_y = _image_cy - _window_cy;
		}
	}


	//-----------------------------------------------------------------------
	_document_viewport_x = _image_viewport_x / _scale;
	_document_viewport_y = _image_viewport_y / _scale;
}

void dx2d_window::update_view_scroll(void)
{
	if (_scrollbar_enabled)
	{
		if (_window_cx < _image_cx)
		{
			_view_x_scroll_min = 0;
			_view_x_scroll_max = _image_cx;
			_view_x_scroll_page = _window_cx;
			_view_x_scroll_line = 20;
		}
		else
		{
			_view_x_scroll_min = 0;
			_view_x_scroll_max = 0;
			_view_x_scroll_page = 0;
			_view_x_scroll_line = 0;
		}


		if (_window_cy < _image_cy)
		{
			_view_y_scroll_min = 0;
			_view_y_scroll_max = _image_cy;
			_view_y_scroll_page = _window_cy;
			_view_y_scroll_line = 20;
		}
		else
		{
			_view_y_scroll_min = 0;
			_view_y_scroll_max = 0;
			_view_y_scroll_page = 0;
			_view_y_scroll_line = 0;
		}
	}
	else
	{
		_view_x_scroll_min = 0;
		_view_x_scroll_max = 0;
		_view_x_scroll_page = 0;
		_view_x_scroll_line = 0;

		_view_y_scroll_min = 0;
		_view_y_scroll_max = 0;
		_view_y_scroll_page = 0;
		_view_y_scroll_line = 0;
	}
}

void dx2d_window::update_scrollbar_position(void)
{
	SetScrollInfo64(_hwnd, SB_HORZ, SIF_ALL, _view_x_scroll_max, _image_viewport_x, _view_x_scroll_page, TRUE);
	SetScrollInfo64(_hwnd, SB_VERT, SIF_ALL, _view_y_scroll_max, _image_viewport_y, _view_y_scroll_page, TRUE);
}

//===========================================================================
void dx2d_window::vscroll(std::uint32_t scroll_code)
{
	//-----------------------------------------------------------------------
	std::int64_t pos;


	pos = GetScrollPos64(_hwnd, SB_VERT, SIF_TRACKPOS, _view_y_scroll_max);


	//-----------------------------------------------------------------------
	std::int64_t view_scroll_pos_current;
	std::int64_t view_scroll_pos;


	view_scroll_pos = _image_viewport_y;
	view_scroll_pos_current = scroll(scroll_code, pos,
		_view_y_scroll_page,
		_view_y_scroll_line,
		_view_y_scroll_min,
		_view_y_scroll_max,
		_image_viewport_y
	);


	//-----------------------------------------------------------------------
	if (view_scroll_pos != view_scroll_pos_current)
	{
		_image_viewport_y = view_scroll_pos_current;
		_document_viewport_y = view_scroll_pos_current / _scale;

		update_scrollbar_position();

		repaint();
	}
}

void dx2d_window::hscroll(std::uint32_t scroll_code)
{
	//-----------------------------------------------------------------------
	std::int64_t pos;


	pos = GetScrollPos64(_hwnd, SB_HORZ, SIF_TRACKPOS, _view_x_scroll_max);


	//-----------------------------------------------------------------------
	std::int64_t view_scroll_pos_current;
	std::int64_t view_scroll_pos;


	view_scroll_pos = _image_viewport_x;
	view_scroll_pos_current = scroll(scroll_code, pos,
		_view_x_scroll_page,
		_view_x_scroll_line,
		_view_x_scroll_min,
		_view_x_scroll_max,
		_image_viewport_x
	);


	//-----------------------------------------------------------------------
	if (view_scroll_pos != view_scroll_pos_current)
	{
		_image_viewport_x = view_scroll_pos_current;
		_document_viewport_x = view_scroll_pos_current / _scale;

		update_scrollbar_position();

		repaint();
	}
}

//===========================================================================
std::int64_t dx2d_window::scroll(
	std::uint32_t scroll_code, std::int64_t scroll_pos,
	std::uint64_t a_view_scroll_page,
	std::uint64_t a_view_scroll_line,
	std::uint64_t a_view_scroll_min,
	std::uint64_t a_view_scroll_max,
	std::uint64_t a_view_scroll_pos
)
{
	std::int64_t view_scroll_min;
	std::int64_t view_scroll_max;
	std::int64_t view_scroll_top;
	std::int64_t view_scroll_bottom;
	std::int64_t view_scroll_pos;
	std::int64_t view_scroll_pos_current;
	std::int64_t view_scroll_page;
	std::int64_t view_scroll_line;


	//-----------------------------------------------------------------------
	view_scroll_page = a_view_scroll_page;
	view_scroll_line = a_view_scroll_line;


	view_scroll_min = a_view_scroll_min;
	view_scroll_max = a_view_scroll_max;


	view_scroll_top = view_scroll_min;
	if (view_scroll_page < view_scroll_max)
	{
		view_scroll_bottom = view_scroll_max - view_scroll_page;
	}
	else
	{
		view_scroll_bottom = view_scroll_min;
	}


	view_scroll_pos = a_view_scroll_pos;
	view_scroll_pos_current = a_view_scroll_pos;


	//-----------------------------------------------------------------------
	switch (scroll_code)
	{
	case SB_TOP:
		view_scroll_pos_current = view_scroll_top;
		break;

	case SB_BOTTOM:
		view_scroll_pos_current = view_scroll_bottom;
		break;

	case SB_LINEUP:
		if (view_scroll_top < (view_scroll_pos - view_scroll_line))
		{
			view_scroll_pos_current = view_scroll_pos - view_scroll_line;
		}
		else
		{
			view_scroll_pos_current = view_scroll_top;
		}
		break;

	case SB_LINEDOWN:
		if ((view_scroll_pos + view_scroll_line) < view_scroll_bottom)
		{
			view_scroll_pos_current = view_scroll_pos + view_scroll_line;
		}
		else
		{
			view_scroll_pos_current = view_scroll_bottom;
		}
		break;

	case SB_PAGEUP:
		if (view_scroll_top < (view_scroll_pos - view_scroll_page))
		{
			view_scroll_pos_current = view_scroll_pos - view_scroll_page;
		}
		else
		{
			view_scroll_pos_current = view_scroll_top;
		}
		break;

	case SB_PAGEDOWN:
		if ((view_scroll_pos + view_scroll_page) < view_scroll_bottom)
		{
			view_scroll_pos_current = view_scroll_pos + view_scroll_page;
		}
		else
		{
			view_scroll_pos_current = view_scroll_bottom;
		}
		break;

	case SB_THUMBTRACK:
		view_scroll_pos_current = scroll_pos;
		break;

	case SB_THUMBPOSITION:
		view_scroll_pos_current = scroll_pos;
		break;

	case SB_ENDSCROLL:
		break;
	}


	//-----------------------------------------------------------------------
	if (view_scroll_pos_current < view_scroll_top)
	{
		view_scroll_pos_current = view_scroll_top;
	}

	if (view_scroll_bottom < view_scroll_pos_current)
	{
		view_scroll_pos_current = view_scroll_bottom;
	}


	return view_scroll_pos_current;
}

void dx2d_window::enable_scrollbar(bool enable)
{
	_scrollbar_enabled = enable;

	update_view_scroll();
	update_scrollbar_position();
}

//===========================================================================
void dx2d_window::fit_document_to_window(bool vert)
{
	if (vert)
	{
		if (_window_cy)
		{
			set_scale(_window_cy / _document_cy);
		}
	}
	else
	{
		if (_window_cx)
		{
			set_scale(_window_cx / _document_cx);
		}
	}
}

void dx2d_window::zoom(bool zoom_in)
{
	double scale_delta;
	double scale_max;
	double scale_min;


	scale_max = 10.0f;
	scale_min = 0.1f;
	scale_delta = 0.1f;


	double scale;
	int scale_x10;


	get_scale(scale);

	scale_x10 = static_cast<int>((scale + 0.05) * 10);
	scale = scale_x10 / 10.0;


	if (zoom_in)
	{
		scale = scale + scale_delta;
	}
	else
	{
		scale = scale - scale_delta;
	}


	if (scale > scale_max)
	{
		scale = scale_max;
	}
	if (scale < scale_min)
	{
		scale = scale_min;
	}


	set_scale(scale);
}

//===========================================================================
void dx2d_window::repaint(void)
{
	dx2d::render(_hwnd);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




