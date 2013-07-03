#ifndef ROOM_HPP
#define ROOM_HPP

#include <utils/types.hpp>
#include <utils/size.hpp>
#include <utils/point.hpp>
#include <utils/any/any.hpp>

#include <list>
#include <stdexcept>
#include <memory>

class System;

class Room
{
public:
    typedef std::shared_ptr<System> sp_system;

    typedef std::list<Point> type_list_coords;

    Room();

    std::string toJson() const;

    /**
    * \brief Parse a room from a json string.
    * \throws std::invalid_argument if the string's format is invalid.
    */
    static Room fromJson(const std::string& json);

    /**
    * \brief Parse a room from a variant map.
    * \throws std::invalid_argument if the map's content is invalid.
    */
    static Room fromJson(const AnyMap& map);

    void setSquares(const type_list_coords& squares);

    type_list_coords::const_iterator squaresBegin() const;
    type_list_coords::const_iterator squaresEnd() const;

    /**
      * \brief return the vertexes of the polygon making the outer walls of the room
      *
      * For now, returns only a square, //TODO: upgrade the aglorithm
      */
    type_list_coords computeWalls() const;

    /**
    * \brief checks if a geometric position is inside the room.
    */
    bool contains(const PointF &point) const;

    /**
    * \brief checks if the room coordinate correspond to a square in the room.
    */
    bool isSquareInRoom(const Point& point) const;

    std::size_t squareNumber() const;

private:
    sp_system m_system;
    type_list_coords m_squares;
};

#endif // ROOM_HPP
