#include "system.hpp"

#include <cassert>

System::System(type_id level, type_id levelMax, const std::string& icon, const Point& console): m_level(level), m_levelMax(levelMax), m_icon(icon),
    m_console(console)
{}

System* System::fromJson(const std::string& json)
{
    return fromJson(JSon::fromJson(json).toMap());
}

System* System::fromJson(const AnyMap& map)
{
    AnyMap::const_iterator i = map.find("type");
    if(i == map.end())
        return 0;
    System* res = type_factory::instance().create(i->second.toUInt8(), map);
    assert(res);
    return res;
}

uint8_t System::level() const
{
    return m_level;
}

uint8_t System::levelMax() const
{
    return m_levelMax;
}

const std::string& System::icon() const
{
    return m_icon;
}

const Point& System::console() const
{
    return m_console;
}

bool System::isPowerGenerator() const
{
    return false;
}

//void System::setLevel(uint8_t i)
//{
//    m_level = i;
//}

//void System::setLevelMax(uint8_t i)
//{
//    m_levelMax = i;
//}
