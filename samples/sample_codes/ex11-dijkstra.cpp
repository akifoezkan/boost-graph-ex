/* 
 * Example 31.11. Finding paths with dijkstra_shortest_paths() 
 * https://theboostcpplibraries.com/boost.graph-algorithms
 *
 * This algorithm is used if lines are weighted.
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iostream>

// boost::dijkstra_shortest_paths() uses the bundled property of type boost::edge_weight_t
// find shortest path from topLeft -> bottomRight, where the edges are wighted

int main()
{
    enum { topLeft, topRight, bottomRight, bottomLeft };

    std::array<std::pair<int, int>, 4> edges{{
      std::make_pair(topLeft, topRight),
      std::make_pair(topRight, bottomRight),
      std::make_pair(bottomRight, bottomLeft),
      std::make_pair(bottomLeft, topLeft)
    }};

    // 4th parameter - boost::no_property -> default
    // 5th parameter - uses boost::property to define a bundled property
    //  bundled_property<tag, type>
    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS, 
        boost::no_property, boost::property<boost::edge_weight_t, int>> graph;

    std::array<int, 4> weights{{2, 1, 1, 1}};
    graph g{edges.begin(), edges.end(), weights.begin(), 4};

    boost::array<int, 4> directions;
    boost::dijkstra_shortest_paths(g, bottomRight, boost::predecessor_map(directions.begin()));

    std::cout << "Directions to " << bottomRight << std::endl;
    std::for_each(directions.begin(), directions.end(), [](int d){std::cout << d << "\n";});

    std::cout << "Shortest path from " << topLeft << " to " << bottomRight << std::endl;
    int p = topLeft;
    while (p != bottomRight)
    {
      std::cout << p << '\n';
      p = directions[p];
    }
    std::cout << p << '\n';
}
