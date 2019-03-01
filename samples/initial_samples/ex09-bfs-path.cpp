/* 
 * Example 31.9. Finding paths with breadth_first_search() 
 * https://theboostcpplibraries.com/boost.graph-algorithms
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <algorithm>
#include <iostream>

// Find shortest path from topLeft -> bottomRight
// shortest path can be find by following the predecessor vertexes of bfs from start to the end

// Note
// boost::breadth_first_search() can only be used if every line has the same weight. 
// This means the time taken to cross any line between points is always the same. 
// If lines are weighted, meaning that each line may require a different amount of time to 
// traverse, then you need to use a different algorithm to find the shortest path.

int main()
{
    enum { topLeft, topRight, bottomRight, bottomLeft };

    std::array<std::pair<int, int>, 4> edges{{
      std::make_pair(topLeft, topRight),
      std::make_pair(topRight, bottomRight),
      std::make_pair(bottomRight, bottomLeft),
      std::make_pair(bottomLeft, topLeft)
    }};

    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS> graph;
    graph g{edges.begin(), edges.end(), 4};

    boost::array<int, 4> predecessors;
    predecessors[bottomRight] = bottomRight;

    boost::breadth_first_search(g, bottomRight, boost::visitor(
        boost::make_bfs_visitor(boost::record_predecessors(predecessors.begin(), boost::on_tree_edge{}))));

    std::cout << "Predecessor list:" << std::endl;
    std::copy(predecessors.begin(), predecessors.end(), std::ostream_iterator<int>{std::cout, "\n"});

    std::cout << "Shortest distance:" << std::endl;
    int p = topLeft;
    while (p != bottomRight)
    {
      std::cout << p << '\n';
      p = predecessors[p];
    }
    std::cout << p << '\n';
}
