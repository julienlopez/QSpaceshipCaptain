#ifndef SHIP_HPP
#define SHIP_HPP

#include "room.hpp"
#include "door.hpp"

class Ship : public Size<uint8_t>
{
public:
    typedef Size<uint8_t> Size8;
    typedef std::list<Room> type_list_rooms;
    typedef std::list<Door> type_list_doors;

    Ship(const std::string& name = std::string(), const Size8& size = Size8(10, 10));

    const std::string& name() const;

    type_list_rooms::const_iterator roomsBegin() const;
    type_list_rooms::const_iterator roomsEnd() const;

    type_list_doors::const_iterator doorsBegin() const;
    type_list_doors::const_iterator doorsEnd() const;

    //Json methods
    std::string toJson() const;
    static Ship fromJson(const std::string& json) throw(std::invalid_argument);
    static Ship fromJson(const AnyMap& map) throw(std::invalid_argument);

//    Room& getRoomByCoord(const Point& point) throw(std::invalid_argument);
    const Room& getRoomByCoord(const Point& point) const throw(std::invalid_argument);

private:
    std::string m_name;
    type_list_rooms m_rooms;
    type_list_doors m_doors;
};

#endif // SHIP_HPP
