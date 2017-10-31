#pragma once
#include <stack>
#include <string>
#include <iostream>
#include <assert.h>
#include "Behavior.h"

class BehaviorTreeBuilder {

protected:
    Composite* m_currentNode;
    std::vector<Composite*> m_parentNode;
    BehaviorTreeBuilder* addAction(Behavior* child)
    {
        m_currentNode->addChild(child);
        return this;
    }
    BehaviorTreeBuilder* addChild(Composite* child)
    {
        m_parentNode.push_back(child);
        m_currentNode = m_parentNode.back();
        return this;
    }

public:
    virtual ~BehaviorTreeBuilder() {}
    BehaviorTreeBuilder() {}
    BehaviorTreeBuilder(std::vector<Composite*> parentNode) {
        m_parentNode = parentNode;
    }
    BehaviorTreeBuilder* action(Behavior* action)
    {
        return addAction(action);
    }

    BehaviorTreeBuilder* condition(ConditionAction * cond) {
        return addAction(cond);
    }

    BehaviorTreeBuilder* sequence(Sequence * seq) { return addChild(seq); }
    BehaviorTreeBuilder* selector(Selector * sel) { return addChild(sel); }
    BehaviorTreeBuilder* activeSelector(ActiveSelector * actSel) { return addChild(actSel); }
    BehaviorTreeBuilder* parallel(Parallel::Policy forSuccess, Parallel::Policy forFailure) { return addChild(&Parallel(forSuccess, forFailure)); }

    Behavior* build()
    {
        assert(m_currentNode != nullptr);
        return m_currentNode;
    }

    BehaviorTree* end()
    {
        return new RangedBehaviorTree(m_currentNode);
    }

    static void test() {
        ActionVerbose FireAtPlayer("FireAtPlayer"), MoveTowardsPlayer("MoveTowardsPlayer"), MoveToPlayersLastKnownPosition("MoveToPlayersLastKnownPosition"),
            LookAround("LookAround"), MoveToRandomPosition("MoveToRandomPosition");

        ConditionAction IsPlayerVisible("IsPlayerVisible"), IsPlayerInRange("IsPlayerInRange"), HaveWeGotASuspectedLocation("HaveWeGotASuspectedLocation");
        Sequence seq = Sequence();
        ActiveSelector actSel = ActiveSelector();
            BehaviorTree* bt = BehaviorTreeBuilder()
            .activeSelector(&actSel)
            ->sequence(&seq)
            ->condition(&IsPlayerVisible)
            ->activeSelector(&actSel)
            ->sequence(&seq)
            ->condition(&IsPlayerInRange)
            ->action(&FireAtPlayer)
            ->action(&MoveTowardsPlayer)
            ->sequence(&seq)
            ->condition(&HaveWeGotASuspectedLocation)
            ->action(&MoveToPlayersLastKnownPosition)
            ->action(&LookAround)
            ->sequence(&seq)
            ->action(&MoveToRandomPosition)
            ->action(&LookAround)
            ->end();

        bt->tick();

    }


    static void test2() {
        ActionVerbose FireAtPlayer("FireAtPlayer"), MoveTowardsPlayer("MoveTowardsPlayer"), MoveToPlayersLastKnownPosition("MoveToPlayersLastKnownPosition"),
            LookAround("LookAround"), MoveToRandomPosition("MoveToRandomPosition");
        Sequence seq = Sequence();

        ActionVerbose IsPlayerVisible("IsPlayerVisible"), IsPlayerInRange("IsPlayerInRange"), HaveWeGotASuspectedLocation("HaveWeGotASuspectedLocation");

        BehaviorTree* bt = BehaviorTreeBuilder()
            .sequence(&seq)
            ->action(&MoveToRandomPosition)
            ->end();

        bt->tick();
    }
};

