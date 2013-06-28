#include "shipgraph.hpp"
#include <boost/graph/dijkstra_shortest_paths.hpp>

ShipGraph::ShipGraph()
{}

ShipGraph::vertex_descriptor ShipGraph::addVertex(const Point& p)
{
    type_map_vertex_descriptor::iterator i_v = d_mid2vertex.find(p);
    if(i_v != d_mid2vertex.end())
        return i_v->second;

    vertex_descriptor v = add_vertex(d_graph);
    d_graph[v] = p;
    d_mid2vertex[p] = v;
    return v;
}

void ShipGraph::addEdge(const Point& p1, const Point& p2, double length)
{
    vertex_descriptor v1 = addVertex(p1);
    vertex_descriptor v2 = addVertex(p2);
    edge_descriptor e;
    bool inserted;
    boost::tie(e, inserted) = boost::add_edge(v1, v2, d_graph);
    boost::property_map<type_graph, boost::edge_weight_t>::type weightmap = get(boost::edge_weight, d_graph);
    weightmap[e] = length;
}

utils::type_list_points ShipGraph::shortestPath(const Point& from, const Point& to)
{
    utils::type_list_points res;

    std::vector<vertex_descriptor> p(num_vertices(d_graph));
    std::vector<double> d(num_vertices(d_graph));

    boost::dijkstra_shortest_paths(d_graph, d_mid2vertex[from], boost::predecessor_map(&p[0]).distance_map(&d[0]));

    std::vector<vertex_descriptor>::iterator it = std::find(p.begin(), p.end(), to);
    assert(it != p.end());

    double distance = d[std::distance(p.begin(), it)];
    cerr << distance << endl;

    return res;
}
