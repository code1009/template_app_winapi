////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#pragma once





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
class WindowClass
{
	WNDCLASSEXW _WindowClass{ };

public:
	WindowClass();
	virtual ~WindowClass();

public:
	WindowClass(const WindowClass&) = delete;
	WindowClass& operator=(const WindowClass&) = delete;

	WindowClass(WindowClass&&) = delete;
	WindowClass& operator=(WindowClass&&) = delete;

public:
	void registerWindowClass(LPCWSTR className, UINT iconId);
	void unregisterWindowClass(void);
};





