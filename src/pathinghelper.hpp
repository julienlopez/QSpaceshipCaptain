#ifndef PATHINGHELPER_HPP
#define PATHINGHELPER_HPP

#include <utils/typedefs.hpp>

class Ship;

class PathingHelper
{
public:
    /**
    * \brief Compute the best path to go from \c start to \c end on the given ship.
    * \attention the two points passed (\c start and \c end) are both room coordinates, not geometrical coordinates!
    *
    * \arg \c start the starting point (a room coordinate)
    * \arg \c end the destination point (a room coordinate)
    * \throws std::invalid_argument exception thrown if no start and/or end are invalid, ie are not in a room on the given ship.
    */
    static utils::type_list_points simplePathFromTo(const Ship& ship, const Point& start, const Point& end);

    static utils::type_list_points simplePathIntoASingleRoom(const PointF& start, const PointF& end) noexcept;
};

#endif // PATHINGHELPER_HPP
