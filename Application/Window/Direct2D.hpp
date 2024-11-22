/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Direct2D
{
public:
	static ID2D1Factory* _pFactory;
	static IDWriteFactory* _pDWriteFactory;

public:
	static bool newFactory(void);
	static void deleteFactory(void);

public:
	ID2D1HwndRenderTarget* _pRenderTarget{ nullptr };

public:
	Direct2D();
	virtual ~Direct2D();

public:
	Direct2D(const Direct2D&) = delete;
	Direct2D& operator=(const Direct2D&) = delete;

	Direct2D(Direct2D&&) = delete;
	Direct2D& operator=(Direct2D&&) = delete;

protected:
	virtual bool createDeviceResources(HWND hWnd);
	virtual void destroyDeviceResources(void);

public:
	virtual void resize(HWND hWnd, UINT width, UINT height);
	virtual void render(HWND hWnd);
	virtual void on_render(void);
};
