#include "ship.hpp"
#include <utils/json.hpp>

#include <sstream>

Ship::Ship(const std::string& name, const Size8 &size): Size8(size), m_name(name)
{}

const std::string& Ship::name() const
{
    return m_name;
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

Ship Ship::fromJson(const std::string& json)
{
    Ship res;
    AnyMap map = JSon::fromJson(json).toMap();
    res.m_name = map["name"].toString();
    res.setWidth(map["width"].toUInt8());
    res.setHeight(map["height"].toUInt8());
    return res;
}
