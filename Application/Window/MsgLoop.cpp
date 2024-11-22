/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"
#include "MsgLoop.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
MsgLoop::MsgLoop()
{
}

//===========================================================================
MsgLoop::~MsgLoop()
{
}

//===========================================================================
void MsgLoop::addIdleHandler(std::function<void(void)> handler)
{
	_idleHandlers.push_back(handler);
}

//===========================================================================
void MsgLoop::runMsgLoop(void)
{
	//-----------------------------------------------------------------------
	MSG msg;
	BOOL rv;


	do
	{
		rv = ::PeekMessageW(&msg, HWND{}, 0, 0, PM_REMOVE);
		if (rv != 0)
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
		}
		else
		{
			onIdle();
		}
	} while (msg.message != WM_QUIT);
}

void MsgLoop::onIdle(void)
{
	for (auto& handler : _idleHandlers)
	{
		handler();
	}
}
