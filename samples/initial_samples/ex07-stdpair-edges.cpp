/* 
 * Example 31.6. boost::adjacent_vertices() and boost::out_edges() 
 * Example 31.7. Initializing boost::adjacency_list with lines 
 * https://theboostcpplibraries.com/boost.graph-vertices-and-edges#ex.graph_01
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <iostream>

#define DIRECTED_GRAPH 0

// You can pass iterators to the constructor of boost::adjacency_list that refer 
// to objects of type std::pair<int, int>, which define lines

int main()
{
#if DIRECTED_GRAPH == 1
    typedef boost::adjacency_list<> _graph;
#else
    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS> _graph;
#endif

    enum {topLeft, topRight, bottomRight, bottomLeft};

    std::array<std::pair<int, int>, 4> edges{{
        std::make_pair(topLeft, topRight),
        std::make_pair(topRight, bottomRight),
        std::make_pair(bottomRight, bottomLeft),
        std::make_pair(bottomLeft, topLeft)
    }};

    _graph g{edges.begin(), edges.end(), 4};

    std::cout << boost::num_vertices(g) << '\n';
    std::cout << boost::num_edges(g) << '\n';
 
    write_graphviz(std::cout, g);
    g.clear();
}
