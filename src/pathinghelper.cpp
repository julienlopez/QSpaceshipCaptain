#include "pathinghelper.hpp"
#include "ship/ship.hpp"
#include "ship/graph/graphhelper.hpp"
#include "ship/graph/shipgraph.hpp"

utils::type_list_points PathingHelper::simplePathFromTo(const Ship& ship, const Point& start, const Point& end)
{
    const Room& startRoom = ship.getRoomByCoord(start);
    const Room& endRoom = ship.getRoomByCoord(end);
    if(&startRoom == &endRoom) return simplePathIntoASingleRoom(start, end + PointF(0.5, 0.5));

    ShipGraph graph = GraphHelper::buildGraph(ship);

    utils::type_list_points res = graph.shortestPath(start, end);
    if(!res.empty() && res.front() == start)
        res.pop_front();
    return res;
}

utils::type_list_points PathingHelper::simplePathIntoASingleRoom(const PointF&, const PointF& end) noexcept
{
    return {end};
}
