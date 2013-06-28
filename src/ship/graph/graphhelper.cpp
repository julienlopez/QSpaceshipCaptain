#include "graphhelper.hpp"
#include "shipgraph.hpp"
#include <ship/ship.hpp>

ShipGraph GraphHelper::buildGraph(std::shared_ptr<Ship> ship)
{
    ShipGraph g;
    for(auto i = ship->roomsBegin(); i != ship->roomsEnd(); ++i) {
        for(auto j = i->squaresBegin(); j != i->squaresEnd(); ++j) {
            g.addVertex(*j);
        }
    }

    return g;
}
