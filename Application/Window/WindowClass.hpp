////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#pragma once





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
class WindowClass
{
private:
	WNDCLASSEXW _WndClass{ };
	std::wstring _ClassName;

public:
	WindowClass();
	virtual ~WindowClass();

public:
	WindowClass(const WindowClass&) = delete;
	WindowClass& operator=(const WindowClass&) = delete;

	WindowClass(WindowClass&&) = delete;
	WindowClass& operator=(WindowClass&&) = delete;

public:
	void registerWindowClass(LPCWSTR className, UINT id);
	void unregisterWindowClass(void);
};





