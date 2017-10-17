#pragma once
#include <vector>
class FSMTransition;
class FSMState
{
public:
    virtual void onEnter();
    virtual void onUpdate();
    virtual void onExit();
    std::vector<FSMTransition*> transitions;
};

class FSMTransition
{
public:
    virtual bool isValid();
    virtual FSMState* getNextState();
    virtual void onTransition();
};