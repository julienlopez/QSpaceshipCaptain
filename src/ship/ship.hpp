#ifndef SHIP_HPP
#define SHIP_HPP

#include "room.hpp"

#include <list>
//#include <boost/shared_ptr.hpp>

class Ship : public Size<uint8_t>
{
public:
    typedef Size<uint8_t> Size8;

    Ship(const std::string& name = std::string(), const Size8& size = Size8(10, 10));

    const std::string& name() const;


    //Json methods
    std::string toJson() const;
    static Ship fromJson(const std::string& json);

private:
    //typedef boost::shared_ptr<Room> sp_room;
    typedef std::list<Room> type_list_rooms;

    std::string m_name;
    type_list_rooms m_rooms;
};

#endif // SHIP_HPP
