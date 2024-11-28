﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "RuntimeDebug.hpp"
#include "Function.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool centerWindow(HWND hwndWindow)
{
	HWND hwndParent;
	RECT rectWindow, rectParent;


	// make the window relative to its parent
	if ((hwndParent = GetParent(hwndWindow)) != NULL)
	{
		GetWindowRect(hwndWindow, &rectWindow);
		GetWindowRect(hwndParent, &rectParent);

		int nWidth = rectWindow.right - rectWindow.left;
		int nHeight = rectWindow.bottom - rectWindow.top;

		int nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
		int nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;

		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		// make sure that the dialog box never moves outside of the screen
		if (nX < 0) nX = 0;
		if (nY < 0) nY = 0;
		if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
		if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;

		MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);

		return true;
	}

	return false;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring getWindowText(const HWND hwnd)
{
	std::wstring s;


	int length;


	length = ::GetWindowTextLengthW(hwnd);


	if (length > 0)
	{
		s.resize(length + 1, 0);

		::GetWindowTextW(hwnd, const_cast<wchar_t*>(s.data()), length + 1);
	}


	return s;
}

void setWindowText(const HWND hwnd, const std::wstring& s)
{
	::SetWindowTextW(hwnd, s.c_str());
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void moveWindow(const HWND hwnd, const RECT& rect, bool repaint)
{
	::MoveWindow(hwnd,
		rect.left, rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		repaint ? TRUE : FALSE);
}

void setWindowPos(const HWND hwnd, const HWND insertAfter, const RECT& rect, UINT flags)
{
	::SetWindowPos(hwnd,
		insertAfter,
		rect.left, rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		flags);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




