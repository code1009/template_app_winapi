/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace mwa
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MsgLoop
{
private:
	std::vector< std::function<void(void)> > _idleHandlers;

public:
	MsgLoop() = default;

public:
	virtual ~MsgLoop() = default;

public:
	MsgLoop(const MsgLoop&) = delete;
	MsgLoop& operator=(const MsgLoop&) = delete;

	MsgLoop(MsgLoop&&) = delete;
	MsgLoop& operator=(MsgLoop&&) = delete;

public:
	virtual void addIdleHandler(std::function<void(void)> handler);

public:
	virtual void runMsgLoop(void);
	virtual void onIdle(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




