/* 
 * Example 31.14. Random paths with random_spanning_tree() 
 * https://theboostcpplibraries.com/boost.graph-algorithms
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random_spanning_tree.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <random>
#include <iostream>
#include <ctime>
#include <cstdint>

//  Returns random paths 
//  In contrast to boost::dijkstra_shortest_paths(), the starting point isn’t
//  passed directly as a parameter to boost::random_spanning_tree(). It must be
//  passed as a named parameter. That’s why root_vertex() is called on the
//  object of type boost::predecessor_map. 

int main()
{
    enum { topLeft, topRight, bottomRight, bottomLeft };

    std::array<std::pair<int, int>, 4> edges{{
      std::make_pair(topLeft, topRight),
      std::make_pair(topRight, bottomRight),
      std::make_pair(bottomRight, bottomLeft),
      std::make_pair(bottomLeft, topLeft)
    }};

    struct edge_properties {
        int weight;
    };

    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS, boost::no_property> graph;

    graph g{edges.begin(), edges.end(), 4};

    boost::array<int, 4> predecessors;

    std::mt19937 random_num_gen{static_cast<uint32_t>(std::time(0))};
    boost::random_spanning_tree(g, random_num_gen,
        boost::predecessor_map(predecessors.begin()).root_vertex(bottomLeft));

    std::cout << "Directions to " << bottomRight << std::endl;
    std::for_each(predecessors.begin(), predecessors.end(), [](int d){std::cout << d << "\n";});

    std::cout << "Shortest path from " << topRight << " to " << bottomLeft << std::endl;
    int p = topRight;
    while (p != bottomLeft && p != -1)
    {
      std::cout << p << '\n';
      p = predecessors[p];
    }
    std::cout << p << '\n';
}
