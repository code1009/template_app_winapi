////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#include "pch.hpp"
#include "../Window/Application.hpp"
#include "../Window/WindowClass.hpp"
#include "../Window/Window.hpp"
#include "../Resource/Resource.h"
#include "AboutBoxDialog.hpp"





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
constexpr LPCWSTR AboutBoxDialog_ClassName = L"xAboutBoxDialog";





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
AboutBoxDialog::AboutBoxDialog()
{
}

//==============================================================================
AboutBoxDialog::~AboutBoxDialog()
{
}

//==============================================================================
LRESULT AboutBoxDialog::onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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

	return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

//==============================================================================
LRESULT AboutBoxDialog::onInitDialog(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	일반적으로 대화 상자 프로시저는 메시지를 처리한 경우 TRUE 를 반환하고,
	그렇지 않으면 FALSE 를 반환해야 합니다.
	대화 상자 프로시저가 FALSE를 반환하면 대화 관리자가 메시지에 대한 응답으로 
	기본 대화 상자 작업을 수행합니다.
	*/
	return TRUE;
}

LRESULT AboutBoxDialog::onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT AboutBoxDialog::onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT AboutBoxDialog::onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT AboutBoxDialog::onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	
	
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 10, 10, L"AboutBoxDialog", 14);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return TRUE;
}

LRESULT AboutBoxDialog::onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
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

void AboutBoxDialog::onCommand_OK(void)
{
	::EndDialog(_hWnd, IDOK);
}

void AboutBoxDialog::onCommand_Cancel(void)
{
	::EndDialog(_hWnd, IDCANCEL);
}

