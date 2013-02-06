#ifndef ROOM_HPP
#define ROOM_HPP

#include <utils/types.hpp>
#include <utils/size.hpp>
#include <utils/point.hpp>
#include <utils/any/any.hpp>

#include <list>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

class System;

class Room
{
public:
    typedef boost::shared_ptr<System> sp_system;

    typedef std::list<Point> type_list_coords;

    Room();

    std::string toJson() const;

    static Room fromJson(const std::string& json) throw(std::invalid_argument);
    static Room fromJson(const AnyMap& map) throw(std::invalid_argument);

    void setSquares(const type_list_coords& squares);

    type_list_coords::const_iterator squaresBegin() const;
    type_list_coords::const_iterator squaresEnd() const;

    /**
      * \brief return the vertexes of the polygon making the outer walls of the room
      *
      * For now, returns only a square, //TODO: upgrade the aglorithm
      */
    type_list_coords computeWalls() const;

    bool contains(const Point& point) const;

private:
    sp_system m_system;
    type_list_coords m_squares;
};

#endif // ROOM_HPP
