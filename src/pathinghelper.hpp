#ifndef PATHINGHELPER_HPP
#define PATHINGHELPER_HPP

#include <utils/point.hpp>

#include <list>

class Ship;

class PathingHelper
{
public:
    typedef std::list<Point> type_list_points;

    static type_list_points simplePathFromTo(const Ship& ship, const Point& depart, const Point& Arrivee);
};

#endif // PATHINGHELPER_HPP
