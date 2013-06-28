#ifndef GRAPHHELPER_HPP
#define GRAPHHELPER_HPP

#include <memory>

class ShipGraph;
class Ship;

class GraphHelper
{
public:
    GraphHelper() = delete;

    static ShipGraph buildGraph(std::shared_ptr<Ship> ship);
};

#endif // GRAPHHELPER_HPP
