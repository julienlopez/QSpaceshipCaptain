#ifndef ROOM_HPP
#define ROOM_HPP

#include <utils/types.hpp>
#include <utils/size.hpp>
#include <utils/point.hpp>

#include <list>

#include <boost/shared_ptr.hpp>

class System;

class Room : public Size<uint8_t>
{
public:
    typedef Size<uint8_t> Size8;

    typedef boost::shared_ptr<System> sp_system;

    typedef std::list<Point> type_list_coords;

    Room(const Size8& size = Size8(2, 2));

    std::string toJson() const;

    static Room fromJson(const std::string& json);

private:
    sp_system m_system;
    type_list_coords m_walls;
    type_list_coords m_squares;

    void computeSquares();
};

#endif // ROOM_HPP
