#include "door.hpp"
#include <utils/json.hpp>

#include <sstream>

Door::Door(const Point& from, const Point& to): m_isOpen(false), m_from(from), m_to(to)
{}

Door::Door(const Door& door): m_isOpen(door.m_isOpen), m_from(door.m_from), m_to(door.m_to)
{}

const Point& Door::from() const
{
    return m_from;
}

const Point& Door::to() const
{
    return m_to;
}

bool Door::isVertical() const
{
    return m_from.x() == m_to.x();
}

bool Door::isHorizontal() const
{
    return m_from.y() == m_to.y();
}

bool Door::isOpen() const
{
    return m_isOpen;
}

void Door::setOpen(bool b)
{
    m_isOpen = b;
}

void Door::open()
{
    m_isOpen = true;
}

void Door::close()
{
    m_isOpen = false;
}

std::string Door::toJson() const
{
    std::ostringstream oss;
    oss << "{ \"from\" : { \"x\" : " << m_from.x() << ", \"y\" : " << m_from.y() << " }, \"to\" : { \"x\" : " << m_from.x() << ", \"y\" : " << m_from.y() << " } }";
    return oss.str();
}

Door Door::fromJson(const std::string& json)
{
    Any map = JSon::fromJson(json);
    return fromJson(map.toMap());
}

Door Door::fromJson(const AnyMap& map)
{
    Door res;

    AnyMap::const_iterator i = map.find("from");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for from");
    AnyMap m = i->second.toMap();
    res.m_from = Point(m["x"].toUInt8(), m["y"].toUInt8());

    i = map.find("to");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for to");
    m = i->second.toMap();
    res.m_to = Point(m["x"].toUInt8(), m["y"].toUInt8());

    return res;
}
