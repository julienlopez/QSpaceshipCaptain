#include "crewmember.hpp"
#include <utils/json.hpp>

#include <sstream>

CrewMember::CrewMember(const std::string& name): m_name(name), m_position(-1, -1)
{}

const std::string& CrewMember::name() const
{
    return m_name;
}

const PointF& CrewMember::position() const
{
    return m_position;
}

void CrewMember::setName(const std::string& name)
{
    m_name = name;
}

void CrewMember::setPosition(const PointF& pos)
{
    m_position = pos;
}

std::string CrewMember::toJson() const
{
    std::ostringstream oss;
    oss << "{ \"name\" : \"" + m_name + "\", \"position\" : { \"x\" : " << m_position.x() << ", \"y\" : " << m_position.y() << "} }";
    return oss.str();
}

CrewMember CrewMember::fromJson(const std::string& json) throw(std::invalid_argument)
{
    AnyMap map = JSon::fromJson(json).toMap();
    return fromJson(map);
}

CrewMember CrewMember::fromJson(const AnyMap& map) throw(std::invalid_argument)
{
    AnyMap::const_iterator i = map.find("name");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for name");
    CrewMember res(i->second.toString());

    return res;
}
