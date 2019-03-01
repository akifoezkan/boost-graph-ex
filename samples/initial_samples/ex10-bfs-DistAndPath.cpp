/* 
 * Example 31.10. Finding distances and paths with breadth_first_search() 
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

    boost::array<int, 4> distances{{0}};
    boost::array<int, 4> predecessors;
    predecessors[bottomRight] = bottomRight;

    // To use two visitors, you need to put them in a pair with std::make_pair(). 
    // If more than two visitors are needed, the pairs have to be nested.
    boost::breadth_first_search(g, bottomRight, boost::visitor(
        boost::make_bfs_visitor(std::make_pair(
            boost::record_distances(distances.begin(), boost::on_tree_edge{}),
            boost::record_predecessors(predecessors.begin(), boost::on_tree_edge{})))));

    std::cout << "Distances to bottomRight (" << bottomRight << ")" << std::endl;
    std::for_each(distances.begin(), distances.end(), [](int d){std::cout << d << "\n";});

    std::cout << "Shortest path:" << std::endl;
    int p = topLeft;
    while (p != bottomRight)
    {
      std::cout << p << '\n';
      p = predecessors[p];
    }
    std::cout << p << '\n';
}
