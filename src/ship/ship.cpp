#include "ship.hpp"
#include <utils/json.hpp>

#include <sstream>

Ship::Ship(const std::string& name, const Size8 &size): Size8(size), m_name(name)
{}

const std::string& Ship::name() const
{
    return m_name;
}

Ship::type_list_rooms::const_iterator Ship::roomsBegin() const
{
    return m_rooms.begin();
}

Ship::type_list_rooms::const_iterator Ship::roomsEnd() const
{
    return m_rooms.end();
}

Ship::type_list_doors::const_iterator Ship::doorsBegin() const
{
    return m_doors.begin();
}

Ship::type_list_doors::const_iterator Ship::doorsEnd() const
{
    return m_doors.end();
}

std::string Ship::toJson() const
{
    std::ostringstream res;
    res << "{ \"name\" : \"" << m_name << "\", \"width\" : " << width() << ", \"height\" : " << height() << " rooms : [";
    std::string str;
    for(type_list_rooms::const_iterator i = m_rooms.begin(); i != m_rooms.end(); ++i)
        str += i->toJson() + ", ";
    str.erase(--str.end());
    res << str;
    return res.str() + "] }";
}

#include <QDebug>

Ship Ship::fromJson(const std::string& json) throw(std::invalid_argument)
{
    qDebug() << QString::fromStdString(json);
    AnyMap map = JSon::fromJson(json).toMap();
    return fromJson(map);
}

Ship Ship::fromJson(const AnyMap& map) throw(std::invalid_argument)
{
    Ship res;
    AnyMap::const_iterator i = map.find("name");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for name");
    res.m_name = i->second.toString();

    i = map.find("width");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for width");
    res.setWidth(i->second.toUInt8());

    i = map.find("height");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for height");
    res.setHeight(i->second.toUInt8());

    i = map.find("rooms");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for rooms");
    AnyList lst = i->second.toList();
    for(AnyList::const_iterator i = lst.begin(); i != lst.end(); ++i)
        res.m_rooms.push_back(Room::fromJson(i->toMap()));

    i = map.find("doors");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for doors");
    lst = i->second.toList();
    for(AnyList::const_iterator i = lst.begin(); i != lst.end(); ++i)
        res.m_doors.push_back(Door::fromJson(i->toMap()));

    i = map.find("starting_spot");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for starting_spot");
    AnyMap m = i->second.toMap();
    res.m_startingSpot.setX(m["x"].toInt8());
    res.m_startingSpot.setY(m["y"].toInt8());

    i = map.find("crew");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for crew");
    lst = i->second.toList();
    for(AnyList::const_iterator i = lst.begin(); i != lst.end(); ++i)
    {
        CrewMember cm = CrewMember::fromJson(i->toMap());
        res.m_crew.push_back(cm);
    }

    return res;
}

const Room& Ship::getRoomByCoord(const Point& point) const throw(std::invalid_argument)
{
    for(type_list_rooms::const_iterator i = m_rooms.begin(); i != m_rooms.end(); ++i)
    {
        if(i->contains(point)) return *i;
    }
    throw std::invalid_argument("Unable to find a room for this point");
}
