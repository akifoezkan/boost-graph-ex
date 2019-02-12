/* 
 * Example 31.12. User-defined properties with dijkstra_shortest_paths()
 * Example 31.13. Initializing user-defined properties at graph definition
 * https://theboostcpplibraries.com/boost.graph-algorithms
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iostream>

#define GRAPH_INIT 1

// Similar to ex11, but uses a user-defined class, edge_properties, rather than 
// a predefined property (boost::edge_weight_t).(graph) g.weight

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
        // It is possible to add more member variables if other properties are required.
        int weight;
    };

    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS,
        boost::no_property, edge_properties> graph;

    
#if GRAPH_INIT
    boost::array<edge_properties, 4> props{{2, 1, 1, 1}};

    graph g{edges.begin(), edges.end(), props.begin(), 4};
#else
    graph g{edges.begin(), edges.end(), 4};

    graph::edge_iterator it, end;
    boost::tie(it, end) = boost::edges(g);
    g[*it].weight = 2;
    g[*++it].weight = 1;
    g[*++it].weight = 1;
    g[*++it].weight = 1;
#endif

    boost::array<int, 4> directions;
    boost::dijkstra_shortest_paths(g, bottomRight,
        boost::predecessor_map(directions.begin()).weight_map(boost::get(&edge_properties::weight, g)));

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
