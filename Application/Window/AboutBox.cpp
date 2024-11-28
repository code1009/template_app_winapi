/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../mwa/RuntimeDebug.hpp"
#include "../mwa/Application.hpp"
#include "../mwa/Window.hpp"

#include "../Resource/Resource.h"

#include "AboutBox.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// 	winver.h(Windows.h 포함)
// Api-ms-win-core-version-l1-1-0.dll
#pragma comment (lib, "Version.lib")





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT AboutBox::onMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
INT_PTR AboutBox::doModal(HWND hWndParent)
{
	INT_PTR rv;


	rv = ::DialogBoxParamW(
		mwa::getApplication()->_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX),
		_hWnd,
		mwa::DialogProc,
		reinterpret_cast<LPARAM>(this)
	);

	return rv;
}

//===========================================================================
LRESULT AboutBox::onInitDialog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	setInformation();

	return TRUE;
}

LRESULT AboutBox::onDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT AboutBox::onClose(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT AboutBox::onSize(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT AboutBox::onEraseBkGnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

LRESULT AboutBox::onPaint(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if 0
	PAINTSTRUCT ps;	
	HDC hdc;
	int bkMode;


	hdc = ::BeginPaint(hWnd, &ps);

	bkMode = ::GetBkMode(hdc);
	::SetBkMode(hdc, TRANSPARENT);
	::TextOutW(hdc, 0, 0, L"AboutBox", 8);
	::SetBkMode(hdc, bkMode);

	::EndPaint(hWnd, &ps);


	return TRUE;
#endif

	return FALSE;
}

LRESULT AboutBox::onCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

void AboutBox::onCommand_OK(void)
{
	::EndDialog(_hWnd, IDOK);
}

void AboutBox::onCommand_Cancel(void)
{
	::EndDialog(_hWnd, IDCANCEL);
}

//===========================================================================
void AboutBox::setInformation(void)
{
	//-----------------------------------------------------------------------
	int v0;
	int v1;
	int v2;
	int v3;


	v0 = 0;
	v1 = 0;
	v2 = 0;
	v3 = 0;


	//-----------------------------------------------------------------------
	wchar_t szFileName[MAX_PATH] = { '\0' };


	GetModuleFileNameW(
		mwa::getApplication()->_hInstance, 
		szFileName, 
		sizeof(szFileName)/sizeof(wchar_t)
	);


	//-----------------------------------------------------------------------
	DWORD dwHandle = 0;
	DWORD dwLen = 0;


	dwLen = GetFileVersionInfoSize(szFileName, &dwHandle);
	if (dwLen)
	{
		std::vector<BYTE> data(dwLen);


		if (GetFileVersionInfoW(szFileName, dwHandle, dwLen, &data[0]))
		{
			VS_FIXEDFILEINFO* pInfo;
			UINT uLen;


			if (VerQueryValueW(&data[0], L"\\", reinterpret_cast<LPVOID*>(&pInfo), &uLen))
			{
				v0 = pInfo->dwProductVersionMS >> 16;
				v1 = pInfo->dwProductVersionMS & 0xffff;
				v2 = pInfo->dwProductVersionLS >> 16;
				v3 = pInfo->dwProductVersionLS & 0xffff;
			}
		}
	}


	//-----------------------------------------------------------------------
	//TCHAR app_version[256];
	wchar_t app_version[256];


	//_stprintf_s(app_version, _T("버젼 %d.%d.%d.%d"),
	swprintf_s(app_version, L"버젼 %d.%d.%d.%d",
		v0,
		v1,
		v2,
		v3
	);

	SetDlgItemTextW(_hWnd, IDC_ABOUTBOX_APP_VERSION, app_version);


	//-----------------------------------------------------------------------
	wchar_t app_name[256];


	LoadStringW(
		mwa::getApplication()->_hInstance, 
		IDS_APPLICATION, 
		app_name, 
		sizeof(app_name)/sizeof(wchar_t)
	);
	SetDlgItemTextW(_hWnd, IDC_ABOUTBOX_APP_NAME, app_name);


	//-----------------------------------------------------------------------
	wchar_t app_note[1024] =
	{
	L"이 컴퓨터 프로그램은 저작권법과 국제 협약의 보호를 받습니다."        L"\r\n"
	L"이 프로그램의 전부 또는 일부를 무단으로 복제, 배포하는 행위는"       L"\r\n"
	L"민사 및 형사법에 의해 엄격히 규제되어 있으며, 기소 사유가 됩니다."   L"\r\n"
	};

	SetDlgItemTextW(_hWnd, IDC_ABOUTBOX_APP_NOTE, app_note);
}




