/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "RuntimeDebug.hpp"
#include "Window.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT Window::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT __stdcall WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCCREATE == uMsg)
	{
		auto userData = reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams;

		::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));

		(reinterpret_cast<Window*>(userData))->_hWnd = hWnd;
	}


	auto windowPtr = reinterpret_cast<Window*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));
	if (windowPtr)
	{
		LRESULT lResult;


		lResult = windowPtr->onMsg(hWnd, uMsg, wParam, lParam);


		if (WM_NCDESTROY == uMsg)
		{
			::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
			//windowPtr->_hWnd = nullptr;
		}


		return lResult;
	}


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
INT_PTR __stdcall DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_INITDIALOG == uMsg)
	{
		auto userData = reinterpret_cast<Window*>(lParam);

		::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));

		(reinterpret_cast<Window*>(userData))->_hWnd = hWnd;
	}


	auto windowPtr = reinterpret_cast<Window*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));
	if (windowPtr)
	{
		LRESULT lResult;


		lResult = windowPtr->onMsg(hWnd, uMsg, wParam, lParam);


		if (WM_NCDESTROY == uMsg)
		{
			::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
			//windowPtr->_hWnd = nullptr;
		}


		return static_cast<INT_PTR>(lResult);
	}


	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




