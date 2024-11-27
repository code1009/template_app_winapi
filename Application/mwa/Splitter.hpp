/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class VSplitter
{
public:
	const int _Width{ 4 };
	COLORREF  _Color;

	double    _Percent;
	int       _OldPos;

public:
	VSplitter();

public:
	void Draw(HWND hWnd);
	void Draw(HWND hWnd, int curPos);
	void UpdateLayout(HWND hWnd, HWND hFirstWnd, HWND hSecondWnd);

public:
	void onLButtonDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onLButtonUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class HSplitter
{
public:
	const int _Width{ 4 };
	COLORREF  _Color;

	double    _Percent;
	int       _OldPos;

public:
	HSplitter();

public:
	void Draw(HWND hWnd);
	void Draw(HWND hWnd, int curPos);
	void UpdateLayout(HWND hWnd, HWND hFirstWnd, HWND hSecondWnd);

public:
	void onLButtonDown(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onLButtonUp(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void onMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




