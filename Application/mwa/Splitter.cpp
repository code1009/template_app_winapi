/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "RuntimeDebug.hpp"
#include "Application.hpp"
#include "WindowClass.hpp"
#include "Window.hpp"
#include "Splitter.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
VSplitter::VSplitter()
{
	_Color = GetSysColor(COLOR_BTNFACE);
	_Percent = 0.8;
	_OldPos = -1;
}

void VSplitter::Draw(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);


	const int maxPos = rect.bottom;


	const int pos = static_cast<int>(maxPos * _Percent);
	Draw(hWnd, pos);
}

void VSplitter::Draw(HWND hWnd, int curPos)
{
	const HDC hdc = GetDC(hWnd);


	if (nullptr == hdc)
	{
		return;
	}


	const HBRUSH hBrush = CreateSolidBrush(_Color);
	const HPEN   hPen = CreatePen(PS_SOLID, 1, _Color);


	if (nullptr == hBrush)
	{
		ReleaseDC(hWnd, hdc);
		return;
	}
	if (nullptr == hPen)
	{
		DeleteObject(hBrush);
		ReleaseDC(hWnd, hdc);
		return;
	}


	RECT rect;
	GetClientRect(hWnd, &rect);


	RECT barRect;
	barRect.left = 0;
	barRect.top = curPos - _Width / 2;
	barRect.right = rect.right;
	barRect.bottom = curPos + _Width / 2;


	//SetROP2(hdc, R2_NOT);
	//SetBkMode(hdc, TRANSPARENT);

	const HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
	const HGDIOBJ hOldPen = SelectObject(hdc, hPen);

	Rectangle(hdc, barRect.left, barRect.top, barRect.right, barRect.bottom);

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);

	DeleteObject(hBrush);
	DeleteObject(hPen);

	ReleaseDC(hWnd, hdc);
}

void VSplitter::UpdateLayout(HWND hWnd, HWND hFirstWnd, HWND hSecondWnd)
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
	int first;
	int second;


	first = static_cast<int>((cy * _Percent) - (_Width / 2));
	second = static_cast<int>(cy - (cy * _Percent) - (_Width / 2));

	::MoveWindow(hFirstWnd, 0, 0, cx, first, TRUE);
	::MoveWindow(hSecondWnd, 0, first + _Width, cx, second, TRUE);
}

void VSplitter::onLButtonDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SetCapture(hWnd);
	_OldPos = -1;
}

void VSplitter::onLButtonUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetCapture() != hWnd)
	{
		return;
	}

	ReleaseCapture();

	if (_OldPos > 0)
	{
		Draw(hWnd, _OldPos);
	}

	SendMessage(hWnd, WM_SIZE, 0, 0);
}

void VSplitter::onMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetCapture() != hWnd)
	{
		return;
	}


	RECT rect;
	GetClientRect(hWnd, &rect);


	const int curPos = GET_Y_LPARAM(lParam);
	const int maxPos = rect.bottom;
	_Percent = static_cast<double>(curPos) / static_cast<double>(maxPos);


	if (_Percent < 0.1)
	{
		_Percent = 0.1;
	}
	else if (_Percent > 0.9)
	{
		_Percent = 0.9;
	}


	const int pos = static_cast<int>(maxPos * _Percent);
	if (_OldPos != pos)
	{
		if (_OldPos > 0)
		{
			Draw(hWnd, _OldPos);
		}

		Draw(hWnd, pos);
		_OldPos = pos;
	}


	SendMessage(hWnd, WM_SIZE, 0, 0);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
HSplitter::HSplitter()
{
	_Color = GetSysColor(COLOR_BTNFACE);
	_Percent = 0.8;
	_OldPos = -1;
}

void HSplitter::Draw(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);


	const int maxPos = rect.right;


	const int pos = static_cast<int>(maxPos * _Percent);
	Draw(hWnd, pos);
}

void HSplitter::Draw(HWND hWnd, int curPos)
{
	const HDC hdc = GetDC(hWnd);


	if (nullptr == hdc)
	{
		return;
	}


	const HBRUSH hBrush = CreateSolidBrush(_Color);
	const HPEN   hPen = CreatePen(PS_SOLID, 1, _Color);


	if (nullptr == hBrush)
	{
		ReleaseDC(hWnd, hdc);
		return;
	}
	if (nullptr == hPen)
	{
		DeleteObject(hBrush);
		ReleaseDC(hWnd, hdc);
		return;
	}


	RECT rect;
	GetClientRect(hWnd, &rect);


	RECT barRect;
	barRect.top = 0;
	barRect.left = curPos - _Width / 2;
	barRect.bottom = rect.right;
	barRect.right = curPos + _Width / 2;


	//SetROP2(hdc, R2_NOT);
	//SetBkMode(hdc, TRANSPARENT);

	const HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
	const HGDIOBJ hOldPen = SelectObject(hdc, hPen);

	Rectangle(hdc, barRect.left, barRect.top, barRect.right, barRect.bottom);

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);

	DeleteObject(hBrush);
	DeleteObject(hPen);

	ReleaseDC(hWnd, hdc);
}

void HSplitter::UpdateLayout(HWND hWnd, HWND hFirstWnd, HWND hSecondWnd)
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
	int first;
	int second;


	first = static_cast<int>((cx * _Percent) - (_Width / 2));
	second = static_cast<int>(cx - (cx * _Percent) - (_Width / 2));

	::MoveWindow(hFirstWnd, 0, 0, first, cy, TRUE);
	::MoveWindow(hSecondWnd, first + _Width, 0, second, cy, TRUE);
}

void HSplitter::onLButtonDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SetCapture(hWnd);
	_OldPos = -1;
}

void HSplitter::onLButtonUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetCapture() != hWnd)
	{
		return;
	}

	ReleaseCapture();

	if (_OldPos > 0)
	{
		Draw(hWnd, _OldPos);
	}

	SendMessage(hWnd, WM_SIZE, 0, 0);
}

void HSplitter::onMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GetCapture() != hWnd)
	{
		return;
	}


	RECT rect;
	GetClientRect(hWnd, &rect);


	const int curPos = GET_X_LPARAM(lParam);
	const int maxPos = rect.right;
	_Percent = static_cast<double>(curPos) / static_cast<double>(maxPos);


	if (_Percent < 0.1)
	{
		_Percent = 0.1;
	}
	else if (_Percent > 0.9)
	{
		_Percent = 0.9;
	}


	const int pos = static_cast<int>(maxPos * _Percent);
	if (_OldPos != pos)
	{
		if (_OldPos > 0)
		{
			Draw(hWnd, _OldPos);
		}

		Draw(hWnd, pos);
		_OldPos = pos;
	}


	SendMessage(hWnd, WM_SIZE, 0, 0);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




