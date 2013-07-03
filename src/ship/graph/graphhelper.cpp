#include "graphhelper.hpp"
#include "shipgraph.hpp"
#include <ship/ship.hpp>

ShipGraph GraphHelper::buildGraph(const Ship& ship)
{
    ShipGraph g;
    for(auto i = ship.roomsBegin(); i != ship.roomsEnd(); ++i) {
        for(auto j = i->squaresBegin(); j != i->squaresEnd(); ++j) {
            for(int dx = -1; dx < 2; dx++)
                for(int dy = -1; dy < 2; dy++)
                {
                    Point p = *j + Point(dx, dy);
                    if(*j != p && i->isSquareInRoom(p))
                    {
                        g.addEdge(*j, p, (PointF(*j)-PointF(p)).length());
                        g.addEdge(p, *j, (PointF(*j)-PointF(p)).length());
                    }
                }
        }
    }

    std::function<void (const Door&)> f = [&g](const Door& d)
    {
        g.addEdge(d.from(), d.to(), 1);
        g.addEdge(d.to() , d.from(), 1);
    };
    ship.foreachDoor(f);

    return g;
}
