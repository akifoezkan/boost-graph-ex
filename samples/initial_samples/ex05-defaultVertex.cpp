/*
 * Example 31.5. Creating indexes automatically with boost::add_edge() 
 * https://theboostcpplibraries.com/boost.graph-vertices-and-edges#ex.graph_01
*/

#include <boost/graph/adjacency_list.hpp>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <iostream>

// It is possible to define a graph without calling boost::add_vertex().
// Boost.Graph adds missing points to a graph automatically if the points
// passed to boost::add_edge() don’t exist.

#define DIRECTED_GRAPH 0

int main()
{
#if DIRECTED_GRAPH == 1
    typedef boost::adjacency_list<> _graph;
#else
    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS> _graph;
#endif
    _graph g;

    enum {topLeft, topRight, bottomRight, bottomLeft};

    boost::add_edge(topLeft, topRight, g);
    boost::add_edge(topRight, bottomRight, g);
    boost::add_edge(bottomRight, bottomLeft, g);
    boost::add_edge(bottomLeft, topLeft, g);

    std::cout << "Edges" << std::endl;
    _graph::edge_iterator it, end;
    std::tie(it, end) = boost::edges(g);
    std::copy(it, end, std::ostream_iterator<_graph::edge_descriptor>{std::cout, "\n"});
}
