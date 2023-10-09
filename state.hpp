#pragma once

namespace one
{
namespace hmi
{
#define NAVI_HANDLE true;
#define NAVI_NOT_HANDLE false;

class CStateMachine;
class CState
{
public:
    CState(CStateMachine & machine) :mStateMachine(machine){}
    
    virtual ~CState() {}
    virtual const char *name() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual bool onCommand(int e, int reason = -1)
    {
        return NAVI_NOT_HANDLE;
    }
protected:
    CStateMachine &mStateMachine;
};

}
}
