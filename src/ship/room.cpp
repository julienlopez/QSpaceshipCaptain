#include "room.hpp"
#include "system.hpp"
#include <utils/json.hpp>

Room::Room()
{}

std::string Room::toJson() const
{
    AnyMap map;
    if(m_system.get()) {
        map["system"] = m_system->toJson();
    }
    return JSon::toJson(map);
}

Room Room::fromJson(const std::string& json) throw(std::invalid_argument)
{
    Any any = JSon::fromJson(json);
    AnyMap map = any.toMap();
    return fromJson(map);
}

Room Room::fromJson(const AnyMap& map) throw(std::invalid_argument)
{
    Room res;
    AnyMap::const_iterator i = map.find("squares");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for squares");
    AnyList squares = i->second.toList();
    for(AnyList::const_iterator i = squares.begin(); i != squares.end(); ++i)
    {
        AnyMap map = i->toMap();
        res.m_squares.push_back(Point(map["x"].toUInt8(), map["y"].toUInt8()));
    }
    i = map.find("system");
    if(i != map.end()) {
        res.m_system.reset(new System(System::fromJson(i->second.toString())));
    }
    return res;
}

void Room::setSquares(const type_list_coords& squares)
{
    m_squares = squares;
}

Room::type_list_coords::const_iterator Room::squaresBegin() const
{
    return m_squares.begin();
}

Room::type_list_coords::const_iterator Room::squaresEnd() const
{
    return m_squares.end();
}

Room::type_list_coords Room::computeWalls() const
{
    type_list_coords res;
    double minX = 1000;
    double minY = 1000;
    double maxX = 0;
    double maxY = 0;
    for(type_list_coords::const_iterator i = squaresBegin(); i != squaresEnd(); ++i)
    {
        minX = std::min<double>(minX, i->x());
        maxX = std::max<double>(maxX, i->x());
        minY = std::min<double>(minY, i->y());
        maxY = std::max<double>(maxY, i->y());
    }
    res.push_back(Point(minX, minY));
    res.push_back(Point(maxX+1, minY));
    res.push_back(Point(maxX+1, maxY+1));
    res.push_back(Point(minX, maxY+1));
    return res;
}

namespace
{
    class PointInRoom
    {
    public:
        PointInRoom(const Point& p): m_topLeft(p)
        {
            m_bottomRight = p + Point(1, 1);
        }
        bool operator()(const Point& square) const
        {
            return square.x() >= m_topLeft.x() && square.x() <= m_bottomRight.x() && square.y() >= m_topLeft.y() && square.y() <= m_bottomRight.y();
        }

    private:
        const Point& m_topLeft;
        Point m_bottomRight;
    };
}

bool Room::contains(const Point& point) const
{
    return std::find_if(m_squares.begin(), m_squares.end(), PointInRoom(point)) != m_squares.end();
}
