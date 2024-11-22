/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//https://github.com/kenjinote/SplitterControl/blob/master/Source.cpp
class VSplitter
{
public:
	const int _Width{ 4 };
	double _percent = 0.8;
	int _oldposx;

public:
	void Draw(HWND hWnd, INT x)
	{
		const HDC hdc = GetDC(hWnd);
		if (hdc)
		{
			//const HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
			const HBRUSH hBrush = CreateSolidBrush(RGB(248, 248, 248));
			const HPEN hPen= CreatePen(PS_SOLID, 1, RGB(248, 248, 248));
			if (hBrush)
			{
				RECT rect;
				GetClientRect(hWnd, &rect);
				const RECT rectSplit = 
				{
					0         , x - _Width / 2,
					rect.right, x + _Width / 2
				};

				//SetROP2(hdc, R2_NOT);
				//SetBkMode(hdc, TRANSPARENT);

				const HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
				const HGDIOBJ hOldPen = SelectObject(hdc, hPen);

				Rectangle(hdc, rectSplit.left, rectSplit.top, rectSplit.right, rectSplit.bottom);
				
				SelectObject(hdc, hOldBrush);
				SelectObject(hdc, hOldPen);

				DeleteObject(hBrush);
				DeleteObject(hPen);
			}
			ReleaseDC(hWnd, hdc);
		}
	}

public:
	void onLButtonDown(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
	{
		SetCapture(hWnd);
		_oldposx = -1;
	}

	void onMouseMove(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (GetCapture() == hWnd)
		{
			const int posx = GET_Y_LPARAM(lParam);


			RECT rect;
			
			
			GetClientRect(hWnd, &rect);
			

			_percent = (double)posx / (double)rect.bottom;


			if (_percent < 0.1) _percent = 0.1;
			else if (_percent > 0.9) _percent = 0.9;


			const int x = (int)(rect.bottom * _percent);


			if (_oldposx != x)
			{
				if (_oldposx > 0) Draw(hWnd, _oldposx);
				Draw(hWnd, x);
				_oldposx = x;
			}

			SendMessage(hWnd, WM_SIZE, 0, 0);
		}
	}

	void onLButtonUp(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (GetCapture() == hWnd)
		{
			ReleaseCapture();

			if (_oldposx > 0) Draw(hWnd, _oldposx);

			SendMessage(hWnd, WM_SIZE, 0, 0);
		}
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class HSplitter
{
public:
	const int _Width{ 4 };
	double _percent = 0.5;
	int _oldposx;

public:
	void Draw(HWND hWnd, INT x)
	{
		const HDC hdc = GetDC(hWnd);
		if (hdc)
		{
			const HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
			if (hBrush)
			{
				RECT rect;
				GetClientRect(hWnd, &rect);
				const RECT rectSplit = { x - _Width / 2, 0, x + _Width / 2, rect.bottom };
				SetROP2(hdc, R2_NOT);
				SetBkMode(hdc, TRANSPARENT);
				const HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
				Rectangle(hdc, rectSplit.left, rectSplit.top, rectSplit.right, rectSplit.bottom);
				SelectObject(hdc, hOldBrush);
				DeleteObject(hBrush);
			}
			ReleaseDC(hWnd, hdc);
		}
	}

public:
	void onLButtonDown(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
	{
		SetCapture(hWnd);
		_oldposx = -1;
	}

	void onMouseMove(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (GetCapture() == hWnd)
		{
			const int posx = GET_X_LPARAM(lParam);


			RECT rect;


			GetClientRect(hWnd, &rect);


			_percent = (double)posx / (double)rect.right;


			if (_percent < 0.1) _percent = 0.1;
			else if (_percent > 0.9) _percent = 0.9;


			const int x = (int)(rect.right * _percent);


			if (_oldposx != x)
			{
				if (_oldposx > 0) Draw(hWnd, _oldposx);
				Draw(hWnd, x);
				_oldposx = x;
			}
		}
	}

	void onLButtonUp(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (GetCapture() == hWnd)
		{
			ReleaseCapture();
			SendMessage(hWnd, WM_SIZE, 0, 0);
		}
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public Window
{
public:
	std::unique_ptr<WidgetView> _WidgetView;
	std::unique_ptr<LogView> _LogView;
	VSplitter _Splitter;

public:
	MainFrame();

public:
	virtual ~MainFrame();

public:
	virtual LRESULT onMsg(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam) override;

public:
	void createWindow(void);
	void destroyWindow(void);

public:
	LRESULT onCreate(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onDestroy(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onClose(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onSize(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onEraseBkGnd(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onPaint(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT onCommand(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);
	void onCommand_App_About(void);
	void onCommand_App_Exit(void);
	LRESULT onNotify(HWND hWnd, uint32_t uMsg, WPARAM wParam, LPARAM lParam);

public:
	void onIdle(void);
};





