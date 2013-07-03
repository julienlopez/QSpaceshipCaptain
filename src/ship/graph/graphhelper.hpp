#ifndef GRAPHHELPER_HPP
#define GRAPHHELPER_HPP

class ShipGraph;
class Ship;

class GraphHelper
{
public:
    GraphHelper() = delete;

    static ShipGraph buildGraph(const Ship& ship);
};

#endif // GRAPHHELPER_HPP
