/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../mwa/RuntimeDebug.hpp"
#include "../mwa/Application.hpp"
#include "../mwa/WindowClass.hpp"
#include "../mwa/Window.hpp"

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
LRESULT LogListViewCtrl::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:     return onCreate       (hWnd, uMsg, wParam, lParam);
	case WM_DESTROY:    return onDestroy      (hWnd, uMsg, wParam, lParam);
	case WM_CLOSE:      return onClose        (hWnd, uMsg, wParam, lParam);
	case WM_SIZE:       return onSize         (hWnd, uMsg, wParam, lParam);
	case WM_ERASEBKGND: return onEraseBkGnd   (hWnd, uMsg, wParam, lParam);
	case WM_PAINT:      return onPaint        (hWnd, uMsg, wParam, lParam);
	case WM_COMMAND:    return onCommand      (hWnd, uMsg, wParam, lParam);
	case OCM_NOTIFY:    return OnNotifyReflect(hWnd, uMsg, wParam, lParam);
	default:
		break;
	}

	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void LogListViewCtrl::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	LPCWSTR   lpszClassName = WC_LISTVIEW;
	LPCWSTR   lpWindowName  = L"Window";
	DWORD     dwStyle       = mwa::ControlWindowStyle;
	DWORD     dwExStyle     = mwa::ControlWindowStyleEx;
	int       X             = 0;
	int       Y             = 0;
	int       nWidth        = 0;
	int       nHeight       = 0;
	HMENU     hMenu         = nullptr;
	HINSTANCE hInstance     = mwa::getApplication()->_hInstance;
	LPVOID    lpParam       = nullptr;


	dwStyle = 0
		| WS_CHILD
		| WS_VISIBLE
		| WS_CLIPSIBLINGS
		| WS_CLIPCHILDREN
		| LVS_REPORT
		| LVS_SHOWSELALWAYS
		| LVS_OWNERDATA
		//| LVS_OWNERDRAWFIXED
		;


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
		hInstance,
		lpParam
	);
	if (nullptr == hWnd)
	{
		throw std::runtime_error("LogListViewCtrl::createWindow() failed");
	}


	//-----------------------------------------------------------------------
	LONG_PTR rv;
	WNDPROC oldWindowProc;


	rv = ::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	rv = ::SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(mwa::WindowProc));
	oldWindowProc = reinterpret_cast<WNDPROC>(rv);
	_PrevWindowProc = oldWindowProc;
	_hWnd = hWnd;


	//-----------------------------------------------------------------------
	DWORD dwListViewExStyle;


	dwListViewExStyle = 0
		| LVS_EX_DOUBLEBUFFER
		| LVS_EX_GRIDLINES 
		| LVS_EX_FULLROWSELECT
		//| LVS_EX_LABELTIP
		//| LVS_EX_SUBITEMIMAGES
		//| LVS_EX_TRANSPARENTBKGND
		;

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
LRESULT LogListViewCtrl::onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

//===========================================================================
LRESULT LogListViewCtrl::OnNotifyReflect(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	NMHDR* hdr = reinterpret_cast<NMHDR*>(lParam);


	switch (hdr->code)
	{
	case LVN_GETDISPINFO: return OnLvnGetDispInfo(hWnd, uMsg, wParam, lParam);
	case NM_CUSTOMDRAW: return OnNmCustomDraw(hWnd, uMsg, wParam, lParam);
		break;

	default:
		break;
	}


	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

//===========================================================================
LRESULT LogListViewCtrl::OnLvnGetDispInfo(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	LV_DISPINFO* pLvDispInfo = reinterpret_cast<LV_DISPINFO*>(lParam);
	LV_ITEM* pLvItem = &pLvDispInfo->item;


	//-----------------------------------------------------------------------
	int row;
	int col;


	row = pLvItem->iItem;
	col = pLvItem->iSubItem;


	//-----------------------------------------------------------------------
	int index;
	int count;
	int item;
	int item_max;


	//count = static_cast<int>(row_max);
	count = 100;


	//item_max = static_cast<int>(col_max);
	item_max = 4;
	item = 999;


	//-----------------------------------------------------------------------
	constexpr bool Reverse = false;
	if (Reverse)
	{
		index = count - row - 1;
	}
	else
	{
		index = row;
	}


	//-----------------------------------------------------------------------
	switch (col)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		item = col;
		break;

	default:
		break;
	}


	//-----------------------------------------------------------------------
	std::wstring text;


	switch (item)
	{
	case 0: text = std::to_wstring(row); break;
	case 1: text = L"TEXT1"; break;
	case 2: text = L"TEXT2"; break;
	case 3: text = L"TEXT3"; break;
	case 4: text = L"TEXT4"; break;
	default:
		break;
	}
	

	//-----------------------------------------------------------------------
	if (pLvItem->mask & LVIF_TEXT)
	{
		if (item_max > item)
		{
			wcsncpy_s(pLvItem->pszText, pLvItem->cchTextMax, text.c_str(), _TRUNCATE);
		}
		else
		{
			wcsncpy_s(pLvItem->pszText, pLvItem->cchTextMax, L" ", _TRUNCATE);
		}
	}


	return 0;
}

//===========================================================================
LRESULT LogListViewCtrl::OnNmCustomDraw(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMCUSTOMDRAW NmCustomDraw = reinterpret_cast<LPNMCUSTOMDRAW>(lParam);


	switch (NmCustomDraw->dwDrawStage)
	{
	case  CDDS_PREPAINT     : return OnPrePaint       (hWnd, uMsg, wParam, lParam);
	case  CDDS_POSTPAINT    : return OnPostPaint      (hWnd, uMsg, wParam, lParam);
	case  CDDS_PREERASE     : return OnPreErase       (hWnd, uMsg, wParam, lParam);
	case  CDDS_POSTERASE    : return OnPostErase      (hWnd, uMsg, wParam, lParam);
	case  CDDS_ITEMPREPAINT : return OnItemPrePaint   (hWnd, uMsg, wParam, lParam);
	case  CDDS_ITEMPOSTPAINT: return OnItemPostPaint  (hWnd, uMsg, wParam, lParam);
	case  CDDS_ITEMPREERASE : return OnItemPreErase   (hWnd, uMsg, wParam, lParam);
	case  CDDS_ITEMPOSTERASE: return OnItemPostErase  (hWnd, uMsg, wParam, lParam);
	case (CDDS_ITEMPREPAINT |
	      CDDS_SUBITEM)     : return OnSubItemPrePaint(hWnd, uMsg, wParam, lParam);

	default:
		break;
	}

	return ::CallWindowProcW(_PrevWindowProc, hWnd, uMsg, wParam, lParam);
}

LRESULT LogListViewCtrl::OnPrePaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDRF_NOTIFYITEMDRAW;
}

LRESULT LogListViewCtrl::OnPostPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDRF_DODEFAULT;
}

LRESULT LogListViewCtrl::OnPreErase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDRF_DODEFAULT;
}

LRESULT LogListViewCtrl::OnPostErase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDRF_DODEFAULT;
}

LRESULT LogListViewCtrl::OnItemPrePaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	NMLVCUSTOMDRAW* pNmLvCustomDraw = reinterpret_cast<NMLVCUSTOMDRAW*>(lParam);

	int row;
	int col;


	row = static_cast<int>(pNmLvCustomDraw->nmcd.dwItemSpec);
	col = static_cast<int>(pNmLvCustomDraw->iSubItem);


	pNmLvCustomDraw->clrText = RGB(0xff, 0x00, 0x00);
	pNmLvCustomDraw->clrTextBk = RGB(0xff, 0xff, 0xff);


	return CDRF_DODEFAULT;
}

LRESULT LogListViewCtrl::OnItemPostPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDRF_DODEFAULT;
}

LRESULT LogListViewCtrl::OnItemPreErase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDRF_DODEFAULT;
}

LRESULT LogListViewCtrl::OnItemPostErase(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDRF_DODEFAULT;
}

LRESULT LogListViewCtrl::OnSubItemPrePaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CDRF_DODEFAULT;
}

//===========================================================================
void LogListViewCtrl::initialize(void)
{
	initializeColumn();
	//initializeItems();
	
	ListView_SetItemCountEx(_hWnd, 100, LVSICF_NOSCROLL);
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
	mwa::WindowClass windowClass;


	windowClass.registerWindowClass(
		LogView_ClassName
	);


	//-----------------------------------------------------------------------
	createWindow(hWndParent);


	//-----------------------------------------------------------------------
	_Control = std::make_unique<LogListViewCtrl>(_hWnd);


	//-----------------------------------------------------------------------
	::ShowWindow(_hWnd, SW_SHOW);
	::UpdateWindow(_hWnd);
}

//===========================================================================
LRESULT LogView::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_NOTIFY:     return onNotify    (hWnd, uMsg, wParam, lParam);
	default:
		break;
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//===========================================================================
void LogView::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	//HWND      hWndParent    = nullptr;
	LPCWSTR   lpszClassName = LogView_ClassName;
	LPCWSTR   lpWindowName  = L"Window";
	DWORD     dwStyle       = mwa::ChildWindowStyle;
	DWORD     dwExStyle     = mwa::ChildWindowStyleEx;
	int       X             = CW_USEDEFAULT;
	int       Y             = CW_USEDEFAULT;
	int       nWidth        = CW_USEDEFAULT;
	int       nHeight       = CW_USEDEFAULT;
	HMENU     hMenu         = nullptr;
	HINSTANCE hInstance     = mwa::getApplication()->_hInstance;
	LPVOID    lpParam       = this;


	dwExStyle |= WS_EX_CLIENTEDGE;


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
		hInstance,
		lpParam
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
LRESULT LogView::onCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//-----------------------------------------------------------------------
	RECT rect;


	GetClientRect(hWnd, &rect);


	//-----------------------------------------------------------------------
	UINT cx;
	UINT cy;


	cx = static_cast<UINT>(rect.right - rect.left);
	cy = static_cast<UINT>(rect.bottom - rect.top);


	//-----------------------------------------------------------------------
	if(_Control.get())
	{
		::MoveWindow(_Control->_hWnd, 0, 0, cx, cy, TRUE);
	}

	return 0;
}

LRESULT LogView::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT LogView::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

LRESULT LogView::onNotify(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	NMHDR* hdr = reinterpret_cast<NMHDR*>(lParam);


	if (_Control.get())
	{
		// 리플렉션된 창 메시지 ID
		// https://learn.microsoft.com/ko-kr/cpp/mfc/reflected-window-message-ids?view=msvc-170&devlangs=cpp&f1url=%3FappId%3DDev17IDEF1%26l%3DKO-KR%26k%3Dk(OCM_NOTIFY)%3Bk(DevLang-C%252B%252B)%3Bk(TargetOS-Windows)%26rd%3Dtrue
		
		// Do notification reflection if message came from a child window.
		// Restricting OnNotifyReflect to child windows avoids double handling.
		if (hdr->hwndFrom == _Control->_hWnd)
		{
			return ::SendMessage(_Control->_hWnd, OCM_NOTIFY, wParam, lParam);
		}
	}

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}



