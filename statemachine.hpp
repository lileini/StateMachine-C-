#pragma once
#include <vector>
#include <map>
#include <algorithm>

#include "state.hpp"

namespace one
{
namespace hmi
{



class CStateMachine
{
public:
    CStateMachine(){}
    virtual ~CStateMachine() {}

    virtual const char *name() { return nullptr; }
    void addState(CState *st);

    void addState(CState *st, CState *parentSt);
    
    void setState(CState *dst);
    
    void command(int e, int reson = -1);

    bool setLastStateName(const std::string &name);

    //bool setCurrentStateName(const std::string &name);
    inline std::string getCurrentStateName()
    {
        if (mState)
        {
            return mState->name();
        }
        return nullptr;
    }
    inline CState *getCurrentState()
    {
        return mState;
    }
    inline void setInitialState(CState* st)
    {
        mState = st;
    }

private:
    CState* mState = nullptr;
    std::string mCurrentStatusName;
    std::map<CState*, CState*> mStateMap;
    std::vector<CState*> mStateList;
};
}
}
