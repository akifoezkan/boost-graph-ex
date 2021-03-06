/*
 * Example 31.6. boost::adjacent_vertices() and boost::out_edges() 
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

    std::cout << "Adjacent Vertices to topLeft (0)" << std::endl;
    _graph::adjacency_iterator vit, vend;
    std::tie(vit, vend) = boost::adjacent_vertices(topLeft, g);
    std::copy(vit, vend, std::ostream_iterator<_graph::vertex_descriptor>{std::cout, "\n"});

    std::cout << "outer adjacent vertices to (outgoing lines from) topLeft (0)" << std::endl;
    _graph::out_edge_iterator eit_o, eend_o;
    std::tie(eit_o, eend_o) = boost::out_edges(topLeft, g);
    std::for_each(eit_o, eend_o, [&g](_graph::edge_descriptor it){ std::cout << boost::target(it, g) << '\n'; });

#if DIRECTED_GRAPH == 0
    std::cout << "inner adjacent vertices to (ingoing lines from) topLeft (0)" << std::endl;
    _graph::in_edge_iterator eit, eend;
    std::tie(eit, eend) = boost::in_edges(topLeft, g);
    std::for_each(eit, eend, [&g](_graph::edge_descriptor it){ std::cout << boost::source(it, g) << '\n'; });
#endif
}
