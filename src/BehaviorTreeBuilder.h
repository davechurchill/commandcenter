#pragma once
#include <stack>
#include <assert.h>
#include "Behavior.h"

class BehaviorTreeBuilder {

protected:
    Behavior* m_currentNode;
    std::stack<Composite*> m_parentNode;
    BehaviorTreeBuilder* addChild(Composite* child)
    {
        if (!m_parentNode.empty()) m_parentNode.top()->addChild(child);
        m_parentNode.push(child);
        return this;
    }

public:
    virtual ~BehaviorTreeBuilder() {}

    BehaviorTreeBuilder* action(Behavior* action)
    {
        assert(m_parentNode.empty());
        m_parentNode.top()->addChild(action);
        return this;
    }

    BehaviorTreeBuilder* condition(bool pred)  { 
        return action(&ConditionAction(pred));  
    }

    BehaviorTreeBuilder* sequence()  { return addChild(&Sequence()); }
    BehaviorTreeBuilder* selector() { return addChild(&Selector()); }
    BehaviorTreeBuilder* activeSelector() { return addChild(&ActiveSelector()); }
    BehaviorTreeBuilder* parallel(Parallel::Policy forSuccess, Parallel::Policy forFailure) { return addChild(&Parallel(forSuccess, forFailure)); }

    Behavior* build()
    {
        assert(m_currentNode == nullptr);
        return m_currentNode;
    }

    BehaviorTreeBuilder* end() 
    {
        m_currentNode = m_parentNode.top();
        return this;
    }

};

class ActionVerbose : public Behavior {
private:
    std::string name;
public:
    ActionVerbose(const std::string n) : name(n) {}
private:
    virtual Status update() override {
        std::cout << name << " succeeded." << std::endl;
        return Status::BH_SUCCESS;
    }
};