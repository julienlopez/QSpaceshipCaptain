#include "ship.hpp"
#include <utils/json.hpp>
#include <utils/comparatormethodvalue.hpp>
#include "systems/system.hpp"

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

//Ship::type_list_doors::const_iterator Ship::doorsBegin() const
//{
//    return m_doors.begin();
//}

//Ship::type_list_doors::const_iterator Ship::doorsEnd() const
//{
//    return m_doors.end();
//}

void Ship::foreachDoor(std::function<void (const Door&)>& functor) const
{
    std::for_each(m_doors.begin(), m_doors.end(), functor);
}

Ship::type_list_crew::const_iterator Ship::crewBegin() const
{
    return m_crew.begin();
}

Ship::type_list_crew::const_iterator Ship::crewEnd() const
{
    return m_crew.end();
}

void Ship::foreachCrew(std::function<void (const CrewMember&)>& functor) const
{
    std::for_each(m_crew.begin(), m_crew.end(), functor);
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
    AnyMap map = JSon::fromJson(json).toMap();
    return fromJson(map);
}

Ship Ship::fromJson(const AnyMap& map)
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
    res.m_startingSpot.setX(m["x"].toDouble());
    res.m_startingSpot.setY(m["y"].toDouble());

    i = map.find("crew");
    if(i == map.end()) throw std::invalid_argument("Unable to find value for crew");
    lst = i->second.toList();
    for(AnyList::const_iterator i = lst.begin(); i != lst.end(); ++i)
    {
        CrewMember cm = CrewMember::fromJson(i->toMap());
        res.add(cm);
    }

    return res;
}

const Room& Ship::getRoomByCoord(const PointF& point) const
{
    for(type_list_rooms::const_iterator i = m_rooms.begin(); i != m_rooms.end(); ++i)
    {
        if(i->contains(point)) return *i;
    }
    throw std::invalid_argument("Unable to find a room for this point");
}

namespace {
class CompareByLengthToSquare {
public:
    CompareByLengthToSquare(const PointF& center): d_center(center)
    {}

    bool operator()(const PointF& p1, const PointF& p2) const
    {
        return (p1-d_center).dot() < (p2-d_center).dot();
    }

private:
    const PointF& d_center;
};
}

#include <QDebug>

void Ship::add(CrewMember crewMember)
{
    if(crewMember.position() == Point(-1, -1))
    {
        if(isThereCrewAtPosition(m_startingSpot))
        {
            //starting spot already taken, looking for the closest free one
            const Room& room = getRoomByCoord(m_startingSpot);
            Room::type_list_coords squares(room.squaresBegin(), room.squaresEnd());
            assert(!squares.empty());
            squares.sort(CompareByLengthToSquare(m_startingSpot));
            Point p(m_startingSpot.x(), m_startingSpot.y());
            while(!squares.empty() && isThereCrewAtPosition(squares.front())) squares.pop_front();
            if(squares.empty())
            {
                qDebug() << "no square left!";
                assert(0 && "TODO"); //TODO sort this out
            }
            else
                crewMember.setPosition(squares.front() + PointF(0.5, 0.5));
        }
        else
            crewMember.setPosition(m_startingSpot);
    }
    m_crew.push_back(crewMember);
}

CrewMember& Ship::memberByName(const std::string& name) {
    for(type_list_crew::iterator i = m_crew.begin(); i != m_crew.end(); ++i) {
        if(i->name() == name) return *i;
    }
    throw std::invalid_argument("No crew member with name " + name);
}

bool Ship::isThereCrewAtPosition(const PointF& position) const
{
    type_list_crew::const_iterator i = std::find_if(m_crew.begin(), m_crew.end(), ComparatorMethodValue<CrewMember, PointF>(&CrewMember::position, position));
    return i != m_crew.end();
}

void Ship::update(double dt)
{
    std::for_each(m_crew.begin(), m_crew.end(), std::bind(std::mem_fun_ref(&CrewMember::update), std::placeholders::_1, dt));
}

Room::cwp_system Ship::powerGenerator() const
{
    for(const Room& r : m_rooms)
    {
        Room::cwp_system s = r.system();
        auto syst = s.lock();
        if(!syst) continue;
        if(syst->isPowerGenerator())
            return syst;
    }
    return Room::cwp_system();
}

uint8_t Ship::energyProduced() const
{
    Room::cwp_system gen = powerGenerator();
    auto generator = gen.lock();
    if(!generator) return 0;
    return generator->level();
}
