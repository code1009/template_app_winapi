////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#pragma once





////////////////////////////////////////////////////////////////////////////////
//==============================================================================
class WindowMsgLoop
{
public:
	WindowMsgLoop();
	virtual ~WindowMsgLoop();

public:
	WindowMsgLoop(const WindowMsgLoop&) = delete;
	WindowMsgLoop& operator=(const WindowMsgLoop&) = delete;

	WindowMsgLoop(WindowMsgLoop&&) = delete;
	WindowMsgLoop& operator=(WindowMsgLoop&&) = delete;

public:
	virtual void run(void);
};



