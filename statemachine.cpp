#include "statemachine.hpp"
#include "common/CSignalDispatcher.hpp"
#include <include/CLogHelper.hpp>
namespace one
{
namespace hmi
{
#ifdef _TSP_LOG_
LOG_DEF_TAG(SM, CStateMachine)
#else
#define SM "CStateMachine"
#endif

void CStateMachine::addState(CState *st)
{
    addState(st, nullptr);
}
void CStateMachine::addState(CState *st, CState *parentSt)
{
    if (st == nullptr)
    {
        LOG_E(SM, "%s state is null",__FUNCTION__);
        return;
    }
    if (std::find(mStateList.begin(), mStateList.end(), st) == mStateList.end())
    {
        mStateList.push_back(st);
        if (parentSt != nullptr)
        {
            mStateMap[st] = parentSt;
        }
    }
}

void CStateMachine::setState(CState *dst)
{
    if (dst == nullptr) 
    {
        LOG_E(SM, "%s state is null", __FUNCTION__);
        return;
    }
    if (dst == mState) 
    {
        LOG_E(SM, "%s dst state is same to current", __FUNCTION__);
        return;
    }
    LOG_I(SM, "change from %s to %s", mState->name(), dst->name());
    setLastStateName(mState->name());
    mState->exit();
    mState = dst;
    dst->enter();
}

void CStateMachine::command(int e, int reason)
{
    LOG_I(SM, "%s command  e:%d r:%d", mState->name(), e, reason);
    CState *st = mState;
    while (st && !st->onCommand(e, reason))
    {
        st = mStateMap[st];
    }
}
bool CStateMachine::setLastStateName(const std::string &name)
{
    return false;
}

}
}