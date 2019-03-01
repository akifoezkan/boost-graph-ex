/* 
 * Example 31.8. Visiting points from inside to outside with breadth_first_search() 
 * https://theboostcpplibraries.com/boost.graph-algorithms
 *
 * A distance is the number of lines that have to be crossed to get from one point to another
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iterator>
#include <algorithm>
#include <iostream>

#define DIRECTED_GRAPH 0

int main()
{
#if DIRECTED_GRAPH == 1
    typedef boost::adjacency_list<> _graph;
#else
    // template parameters: (S)electors
    // boost::SetS uses std::set (map with a key, so no duplicates) for the container
    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS> _graph;
    //typedef boost::adjacency_list<boost::setS, boost::vecS, boost::bidirectionalS> _graph;
#endif

    enum {topLeft, topRight, bottomRight, bottomLeft};

    std::array<std::pair<int, int>, 4> edges{{
        std::make_pair(topLeft, topRight),
        std::make_pair(topRight, bottomRight),
        std::make_pair(bottomRight, bottomLeft),
        std::make_pair(bottomLeft, topLeft)
    }};

    _graph g{edges.begin(), edges.end(), 4};
    boost::array<int, 4> distances{{0}};

    // Here we call boost:bsd_search only with the interested parameters:
    // The first two parameters are the graph and the start point, which are required. 
    // However, the third parameter can be nearly everything
    boost::breadth_first_search(g, topLeft, boost::visitor( 
        boost::make_bfs_visitor(boost::record_distances(distances.begin(), boost::on_tree_edge{}))));

    std::copy(distances.begin(), distances.end(),
      std::ostream_iterator<int>{std::cout, "\n"});

    g.clear();
}
