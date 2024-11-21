/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../mwa/RuntimeDebug.hpp"
#include "../mwa/Application.hpp"
#include "../mwa/Window.hpp"
#include "../mwa/Function.hpp"

#include "../Resource/Resource.h"

#include "PropertyBox.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
PropertyBox::PropertyBox(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	_hWndParent = hWndParent;


	//-----------------------------------------------------------------------
	createWindow(hWndParent);


	//-----------------------------------------------------------------------
	::ShowWindow(_hWnd, SW_SHOW);
}

//===========================================================================
LRESULT PropertyBox::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: return onInitDialog(hWnd, uMsg, wParam, lParam);
	case WM_DESTROY:    return onDestroy   (hWnd, uMsg, wParam, lParam);
	case WM_CLOSE:      return onClose     (hWnd, uMsg, wParam, lParam);
	case WM_SIZE:       return onSize      (hWnd, uMsg, wParam, lParam);
	case WM_PAINT:      return onPaint     (hWnd, uMsg, wParam, lParam);
	case WM_COMMAND:    return onCommand   (hWnd, uMsg, wParam, lParam);
	default:
		break;
	}

	/*
	일반적으로 대화 상자 프로시저는 메시지를 처리한 경우 TRUE 를 반환하고,
	그렇지 않으면 FALSE 를 반환해야 합니다.
	대화 상자 프로시저가 FALSE를 반환하면 대화 관리자가 메시지에 대한 응답으로
	기본 대화 상자 작업을 수행합니다.
	*/
	return FALSE;
}

//===========================================================================
void PropertyBox::createWindow(HWND hWndParent)
{
	//-----------------------------------------------------------------------
	HWND hWnd;


	// Creates a modeless dialog box from a dialog box template resource.
	hWnd = ::CreateDialogParamW(
		mwa::getApplication()->_hInstance, 
		MAKEINTRESOURCE(IDD_ABOUTBOX), 
		hWndParent,
		mwa::DialogProc,
		reinterpret_cast<LPARAM>(this)
	);
	if (nullptr == hWnd)
	{
		throw std::runtime_error("PropertyBox::createWindow() failed");
	}
}

void PropertyBox::destroyWindow(void)
{
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
	}
	_hWnd = nullptr;
}

//===========================================================================
LRESULT PropertyBox::onInitDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	mwa::centerWindow(_hWnd);

	return TRUE;
}

LRESULT PropertyBox::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (::IsWindow(_hWndParent))
	{
		PostMessage(_hWndParent, WM_USER + 0, 2, 0);
	}

	return FALSE;
}

LRESULT PropertyBox::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	destroyWindow();
	return TRUE;
}

LRESULT PropertyBox::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT PropertyBox::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT PropertyBox::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if 0
	PAINTSTRUCT ps;	
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 0, 0, L"PropertyBox", 1);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return TRUE;
#endif

	return FALSE;
}

LRESULT PropertyBox::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int id = LOWORD(wParam);


	switch (id)
	{
	case IDOK:
		onCommand_OK();
		return TRUE;

	case IDCANCEL:
		onCommand_Cancel();
		return TRUE;

	default:
		break;
	}

	return FALSE;
}

void PropertyBox::onCommand_OK(void)
{
	destroyWindow();
}

void PropertyBox::onCommand_Cancel(void)
{
	destroyWindow();
}
