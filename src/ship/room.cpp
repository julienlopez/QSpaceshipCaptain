#include "room.hpp"
#include "system.hpp"
#include <utils/json.hpp>

Room::Room(const Size8 &size): Size8(size)
{}

std::string Room::toJson() const
{
    AnyMap map;
    map["width"] = width();
    map["height"] = height();
    if(m_system.get()) {
        map["system"] = m_system->toJson();
    }
    return JSon::toJson(map);
}

Room Room::fromJson(const std::string& json)
{
    Room res;
    Any any = JSon::fromJson(json);
    AnyMap map = any.toMap();
    res.setWidth(map["width"].toUInt8());
    res.setHeight(map["height"].toUInt8());
    AnyMap::const_iterator i = map.find("system");
    if(i != map.end()) {
        res.m_system.reset(new System(System::fromJson(i->second.toString())));
    }
    return res;
}

void Room::computeSquares()
{
    m_squares.clear();
    if(m_walls.empty()) return;
    type_list_coords::const_iterator it = m_walls.begin();
    ++it;
    for(; it != m_walls.end(); ++it)
    {
        type_list_coords::const_iterator previous = it;
        --previous;
        Point line = *it - *previous;
    }
}
