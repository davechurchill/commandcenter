#include "Condition.h"
#include "CardType.h"

using namespace MCDS;

Condition::Condition()
    : _typeID(0)
    , _isTech(false)
    , _notBlocking(false)
    , _healthAtMost(0)
    , _hasHealthCondition(false)
{
}

Condition::Condition(const rapidjson::Value & value)
    : Condition()
{
    MCDS_ASSERT(value.IsObject(), "Condition was not an Object");
    
    if (value.HasMember("card"))
    {
        MCDS_ASSERT(value["card"].IsString(), "card arg in Condition is not a bool");
        _cardName = value["card"].GetString();
    }
    
    if (value.HasMember("notBlocking"))
    {
        MCDS_ASSERT(value["notBlocking"].IsBool(), "notBlocking arg in Condition is not a bool");
        _notBlocking = value["notBlocking"].GetBool();
    }

    if (value.HasMember("isABC"))
    {
        MCDS_ASSERT(value["isABC"].IsInt(), "isABC arg in Condition is not an int");
        _isTech = (value["isABC"].GetInt() == 1);
    }

    if (value.HasMember("healthAtMost"))
    {
        _hasHealthCondition = true;
        _healthAtMost = value["healthAtMost"].GetInt();
    }
}


const bool Condition::isTech() const
{
    return _isTech;
}

const bool Condition::isNotBlocking() const
{
    return _notBlocking;
}

const CardID & Condition::getTypeID() const
{
    if (_typeID == 0)
    {
        _typeID = CardTypes::GetCardType(_cardName).getID();
    }

    return _typeID;
}

const CardType & Condition::getType() const
{
    return CardTypes::GetAllCardTypes()[getTypeID()];
}

const bool Condition::hasCardType() const
{
    return _cardName.length() > 0;
}

const bool Condition::hasHealthCondition() const
{
    return _hasHealthCondition;
}

const HealthType Condition::getHealthAtMost() const
{
    return _healthAtMost;
}

bool Condition::operator == (const Condition & rhs) const
{
    if (_cardName != rhs._cardName) return false;
    if (_healthAtMost != rhs._healthAtMost) return false;
    if (_isTech != rhs._isTech) return false;
    if (_notBlocking != rhs._notBlocking) return false;
    if (_hasHealthCondition != rhs._hasHealthCondition) return false;
    return true;
}