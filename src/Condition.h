#pragma once

#include "Common.h"

class CCBot;

namespace ConditionTypes
{
    enum { UnaryString, UnaryInt, UnaryUnitType, BinaryComp, BinaryBool, BinaryInt, Invalid };
}

namespace ConditionOperators
{
    enum { LT, GT, EQ, NEQ, LTE, GTE, OR, AND, PLUS, MINUS, MULT, DIV, Invalid };
}

class Condition
{
    CCBot *     m_bot;
    int         m_type;
    int         m_player;
    Condition * m_lhs;
    Condition * m_rhs;
    int         m_op;
    std::string m_strValue;
    int         m_intValue;
    json        m_json;
        
    static int GetOperator(const std::string & op);
    static int GetPlayer(const std::string & op);
    static int GetType(const std::string & op);

public:

    Condition();
    Condition(const json & j, CCBot & bot);
    
    bool eval() const;
    int intEval() const;
};
