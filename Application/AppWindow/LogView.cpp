/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "../Window/Direct2D.hpp"
#include "../Resource/Resource.h"
#include "LogView.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LogListViewCtrl::LogListViewCtrl(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	createWindow(hWndParent);
}

//===========================================================================
LogListViewCtrl::~LogListViewCtrl()
{
}

//===========================================================================
LRESULT LogListViewCtrl::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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

	return ::CallWindowProcW(_ListViewWindowProc, hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void LogListViewCtrl::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	LPCWSTR lpszClassName = WC_LISTVIEW;
	LPCWSTR lpWindowName  = L"Window";
	DWORD   dwStyle       = WS_CHILD | WS_VISIBLE;
	DWORD   dwExStyle     = 0;
	int     X             = 0;
	int     Y             = 0;
	int     nWidth        = 0;
	int     nHeight       = 0;
	HMENU   hMenu         = nullptr;


	dwStyle =
		WS_CHILD |
		WS_VISIBLE |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN |
		LVS_REPORT |
		LVS_SHOWSELALWAYS |
		//LVS_OWNERDATA |
		//LVS_OWNERDRAWFIXED |
		0u;


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
		nullptr
	);
	if (nullptr == hWnd)
	{
		throw std::runtime_error("LogListViewCtrl::createWindow() failed");
	}


	//-----------------------------------------------------------------------
	LONG_PTR rv;
	WNDPROC oldWindowProc;


	rv = ::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	rv = ::SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));
	oldWindowProc = reinterpret_cast<WNDPROC>(rv);
	_ListViewWindowProc = oldWindowProc;
	_hWnd = hWnd;


	//-----------------------------------------------------------------------
	DWORD dwListViewExStyle;


	dwListViewExStyle =
		LVS_EX_DOUBLEBUFFER |
		LVS_EX_GRIDLINES |
		LVS_EX_FULLROWSELECT |
		//LVS_EX_LABELTIP |
		//LVS_EX_SUBITEMIMAGES |
		//LVS_EX_TRANSPARENTBKGND |
		0u;

	ListView_SetExtendedListViewStyleEx(hWnd, dwListViewExStyle, dwListViewExStyle);


	//-----------------------------------------------------------------------
	initialize();
}

void LogListViewCtrl::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}
	_hWnd = nullptr;
}

//===========================================================================
LRESULT LogListViewCtrl::onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_ListViewWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_ListViewWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_ListViewWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_ListViewWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_ListViewWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_ListViewWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_ListViewWindowProc, hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void LogListViewCtrl::initialize(void)
{
	initializeColumn();
	initializeItems();
}

void LogListViewCtrl::initializeColumn(void)
{
	//-----------------------------------------------------------------------
	LVCOLUMNW lvc[] =
	{
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT,  80, const_cast<LPWSTR>(L"번호"  ), 0, 0, 0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT, 100, const_cast<LPWSTR>(L"날짜"  ), 0, 0, 0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT, 120, const_cast<LPWSTR>(L"시간"  ), 0, 0, 0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT, 100, const_cast<LPWSTR>(L"구분"  ), 0, 0, 0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT, 800, const_cast<LPWSTR>(L"내용"  ), 0, 0, 0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT, 100, const_cast<LPWSTR>(L"쓰레드"), 0, 0, 0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT, 150, const_cast<LPWSTR>(L"파일"  ), 0, 0, 0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT,  50, const_cast<LPWSTR>(L"줄"    ), 0, 0, 0, 0 },
		{ LVCF_TEXT | LVCF_WIDTH | LVCF_FMT, LVCFMT_LEFT, 300, const_cast<LPWSTR>(L"함수"  ), 0, 0, 0, 0 }
	};


	//-----------------------------------------------------------------------
	int col;


	for (col = 0; col < sizeof(lvc) / sizeof(lvc[0]); ++col)
	{
		ListView_InsertColumn(_hWnd, col, &lvc[col]);
	}
}

void LogListViewCtrl::initializeItems(void)
{
	//-----------------------------------------------------------------------
	LVITEMW lvi = {};
	int i;
	std::wstring text;


	for (i = 0; i < 100; i++)
	{
		text = std::to_wstring(i);
		lvi.mask = LVIF_TEXT | LVIF_COLUMNS; // LVIF_IMAGE;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.iImage = 0;
		lvi.pszText = const_cast<LPWSTR>(text.c_str());
		lvi.cchTextMax = static_cast<int>(text.size());
		ListView_InsertItem(_hWnd, &lvi);

		text = L"Hello";
		ListView_SetItemText(_hWnd, i, 1, const_cast<LPWSTR>(text.c_str()));
		ListView_SetItemText(_hWnd, i, 2, const_cast<LPWSTR>(text.c_str()));
		ListView_SetItemText(_hWnd, i, 3, const_cast<LPWSTR>(text.c_str()));
		ListView_SetItemText(_hWnd, i, 4, const_cast<LPWSTR>(text.c_str()));
	}
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
constexpr LPCWSTR LogView_ClassName = L"xLogView";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LogView::LogView(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	WindowClass windowClass;


	windowClass.registerWindowClass(
		LogView_ClassName
	);


	//-----------------------------------------------------------------------
	createWindow(hWndParent);


	//-----------------------------------------------------------------------
	_LogListViewCtrl = std::make_unique<LogListViewCtrl>(_hWnd);


	//-----------------------------------------------------------------------
	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);
}

//===========================================================================
LogView::~LogView()
{
}

//===========================================================================
LRESULT LogView::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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
void LogView::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	//HWND    hWndParent    = nullptr;
	LPCWSTR lpszClassName = LogView_ClassName;
	LPCWSTR lpWindowName  = L"Window";
	DWORD   dwStyle       = ChildWindowStyle;
	DWORD   dwExStyle     = WS_EX_CLIENTEDGE;
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
		throw std::runtime_error("LogView::createWindow() failed");
	}
}

void LogView::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}
	_hWnd = nullptr;
}

//===========================================================================
LRESULT LogView::onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	SIZE size{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	UINT type{ (UINT)wParam };


	//-----------------------------------------------------------------------
	RECT rect;


	GetClientRect(hWnd, &rect);


	//-----------------------------------------------------------------------
	UINT cx;
	UINT cy;


	cx = static_cast<UINT>(rect.right - rect.left);
	cy = static_cast<UINT>(rect.bottom - rect.top);


	//-----------------------------------------------------------------------
	if(_LogListViewCtrl.get())
	{
		::MoveWindow(_LogListViewCtrl->_hWnd, 0, 0, cx, cy, TRUE);
	}

	return 0;
}

LRESULT LogView::onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
#if 0
	PAINTSTRUCT ps;
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 0, 0, L"LogView", 7);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return 0;
#endif
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
