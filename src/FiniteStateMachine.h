#pragma once
#include <vector>
#include "sc2api/sc2_api.h"
class CCBot;

class FSMTransition;

class FSMState
{
public:
    virtual void onEnter();
    virtual void onUpdate();
    virtual void onExit();
};

class FSMTransition
{
public:
    virtual bool isValid();
    virtual FSMState* getNextState();
    virtual void onTransition();
};
