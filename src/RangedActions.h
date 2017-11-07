#pragma once
#include "CCBot.h"
#include "Behavior.h"
class KiteAction : public Behavior {
private:
    const sc2::Unit * rangedUnit;
    const sc2::Unit * target;
    CCBot & bot;
    std::unordered_map<sc2::Tag, KitingFiniteStateMachine*> &states;
public:
    KiteAction(
        const sc2::Unit * rangedUnit,
        const sc2::Unit * target,
        CCBot & bot,
        std::unordered_map<sc2::Tag, KitingFiniteStateMachine*> &states
    )
        : rangedUnit(rangedUnit),
        target(target),
        bot(bot),
        states(states) {}
private:
    Status update() {
        Micro::SmartKiteTarget(rangedUnit, target, bot, states);
        return Status::BH_SUCCESS;
    }
};

class FocusFireAction : public Behavior {
private:
    const sc2::Unit * rangedUnit;
    const sc2::Unit * target;
    const std::vector<const sc2::Unit *> * targets;
    CCBot & bot;
    std::unordered_map<sc2::Tag, FocusFireFiniteStateMachine*> &states;
    std::unordered_map<sc2::Tag, float> &unitHealth;
public:
    FocusFireAction(
        const sc2::Unit * rangedUnit,
        const sc2::Unit * target,
        const std::vector<const sc2::Unit *> * targets,
        CCBot & bot,
        std::unordered_map<sc2::Tag, FocusFireFiniteStateMachine*> &states,
        std::unordered_map<sc2::Tag, float> &unitHealth
    )
        : rangedUnit(rangedUnit),
        target(target),
        targets(targets),
        bot(bot),
        states(states),
        unitHealth(unitHealth) {}
private:
    Status update() {
        Micro::SmartFocusFire(rangedUnit, target, targets, bot, states, unitHealth);
        return Status::BH_SUCCESS;
    }
};

class GoToMineralShardAction : public Behavior {
private:
    const sc2::Unit * rangedUnit;
    const sc2::Point2D & targetPosition;
    CCBot & bot;
public:
    GoToMineralShardAction(
        const sc2::Unit * rangedUnit,
        const sc2::Point2D & targetPosition,
        CCBot & bot
    )
        : rangedUnit(rangedUnit),
        targetPosition(targetPosition),
        bot(bot) {}
private:
    Status update() {
        Micro::SmartMove(rangedUnit, targetPosition, bot);
        return Status::BH_SUCCESS;
    }
};

class GoToObjectiveAction : public Behavior {
private:
    const sc2::Unit * rangedUnit;
    const sc2::Point2D & targetPosition;
    CCBot & bot;
public:
    GoToObjectiveAction(
        const sc2::Unit * rangedUnit,
        const sc2::Point2D & targetPosition,
        CCBot & bot
    )
        : rangedUnit(rangedUnit),
        targetPosition(targetPosition),
        bot(bot) {}
private:
    Status update() {
        Micro::SmartMove(rangedUnit, targetPosition, bot);
        return Status::BH_SUCCESS;
    }
};
