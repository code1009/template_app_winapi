/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowClass
{
private:
	std::wstring _ClassName{ };
	WNDCLASSEXW _WndClass{ };

public:
	WindowClass() = default;

public:
	virtual ~WindowClass() = default;

public:
	WindowClass(const WindowClass&) = delete;
	WindowClass& operator=(const WindowClass&) = delete;

	WindowClass(WindowClass&&) = delete;
	WindowClass& operator=(WindowClass&&) = delete;

public:
	void registerWindowClass(
		LPCWSTR className, 
		UINT    idMenu    = 0, 
		UINT    idIcon    = 0, UINT idSmallIcon=0, UINT idCursor=32512/*IDC_ARROW*/, 
		UINT    style     = CS_HREDRAW | CS_VREDRAW
	);
	void unregisterWindowClass(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




