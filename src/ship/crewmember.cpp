#include "crewmember.hpp"
#include <utils/json.hpp>

#include <sstream>
#include <cassert>

CrewMember::CrewMember(const std::string& name): m_name(name), m_position(-1, -1), m_speed(1)
{}

const std::string& CrewMember::name() const noexcept
{
    return m_name;
}

const PointF& CrewMember::position() const noexcept
{
    return m_position;
}

void CrewMember::setName(const std::string& name)
{
    m_name = name;
}

void CrewMember::setPosition(const PointF& pos) noexcept
{
    m_position = pos;
}

std::string CrewMember::toJson() const
{
    std::ostringstream oss;
    oss << "{ \"name\" : \"" + m_name + "\", \"position\" : { \"x\" : " << m_position.x() << ", \"y\" : " << m_position.y() << "} }";
    return oss.str();
}

CrewMember CrewMember::fromJson(const std::string& json)
{
    AnyMap map = JSon::fromJson(json).toMap();
    return fromJson(map);
}

CrewMember CrewMember::fromJson(const AnyMap& map)
{
    AnyMap::const_iterator i = map.find("name");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for name");
    CrewMember res(i->second.toString());

    return res;
}

void CrewMember::followPath(const utils::type_list_points& points)
{
    m_path = points;
}
bool CrewMember::hasNextPosition() const
{
    return !m_path.empty();
}

const PointF& CrewMember::nextPosition() const
{
    if(m_path.empty()) throw std::logic_error("No point to return");
    return m_path.front();
}

const PointF& CrewMember::finalPosition() const
{
    if(m_path.empty()) throw std::logic_error("No point to return");
    return m_path.back();
}

void CrewMember::update(double dt)
{
    if(m_path.empty()) return;
    Vector direction(m_path.front(), position());

    double leftToGo = m_speed * dt;
    if(direction.length() < m_speed * dt)
    {
        leftToGo -= direction.length();
        m_position = m_path.front();
        m_path.pop_front();

        if(m_path.empty()) return;

        direction = Vector(m_path.front(), position());

        assert(direction.length() > leftToGo); //TODO will crash if a segment is smaller than the distance to go through. Should be good for now while dt is small enough.
    }

    direction.normalize();
    direction *= leftToGo;
    m_position += direction;
}
