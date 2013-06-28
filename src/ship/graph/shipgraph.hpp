#ifndef SHIPGRAPH_HPP
#define SHIPGRAPH_HPP

#include <utils/typedefs.hpp>
#include <boost/graph/adjacency_list.hpp>

class ShipGraph
{
public:
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, Point, boost::property<boost::edge_weight_t, double> > type_graph;
    typedef boost::graph_traits<type_graph>::vertex_descriptor vertex_descriptor;
    typedef boost::graph_traits<type_graph>::vertex_iterator vertex_iterator;
    typedef boost::graph_traits<type_graph>::edge_descriptor edge_descriptor;
    typedef boost::graph_traits<type_graph>::edge_iterator edge_iterator;
    typedef std::map<Point, vertex_descriptor> type_map_vertex_descriptor;

    ShipGraph();

    vertex_descriptor addVertex(const Point& p);
    void addEdge(const Point& p1, const Point& p2, double length);

    utils::type_list_points shortestPath(const Point& from, const Point& to);

private:
    type_graph d_graph;
    type_map_vertex_descriptor d_mid2vertex;
};

#endif // SHIPGRAPH_HPP
