/* 
 * https://theboostcpplibraries.com/boost.graph-algorithms
 * Create a graph with vertices for the following countries: Netherlands,
 * Belgium, France, Germany, Switzerland, Austria and Italy. Connect the
 * vertices of those countries with common borders. Find the shortest path –
 * the path with fewest border crossings – to get from Italy to the
 * Netherlands. Write the names of all countries to standard output which you
 * cross on your way from Italy to the Netherlands.
 * 
 * Extend your program: Entering France now costs 10 Euro, entering Belgium 15
 * Euro and entering Germany 20 Euro. Crossing all other borders remains free.
 * Find the shortest path – the path with fewest border crossings – which is
 * also the cheapest path to get from Italy to the Netherlands. Write the names
 * of all countries to standard output which you cross on your way from Italy
 * to the Netherlands.
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iostream>

int main()
{
    enum { Netherlands, Belgium, France, Germany, Switzerland, Austria, Italy };
    const char* name[] = {"Netherlands", "Belgium", "France", "Germany", "Switzerland", "Austria", "Italy"};

    std::array<std::pair<int, int>, 12> edges{{
      std::make_pair(Netherlands, Belgium),
      std::make_pair(Netherlands, Germany),
      std::make_pair(Belgium, France),
      std::make_pair(Belgium, Germany),
      std::make_pair(Germany, France),
      std::make_pair(Germany, Austria),
      std::make_pair(Germany, Switzerland),
      std::make_pair(Switzerland, Italy),
      std::make_pair(Switzerland, France),
      std::make_pair(Switzerland, Austria),
      std::make_pair(Italy, France),
      std::make_pair(Italy, Austria),
    }};

    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, 
        boost::no_property, boost::property<boost::edge_weight_t, int>> _graph;

    std::array<int, 12> weights{};

    for(size_t i = 0; i < edges.size(); i++) {
        switch(edges[i].second) {
            case France : weights[i] = 10; break;
            case Belgium: weights[i] = 15; break;
            case Germany: weights[i] = 20; break;
            default: weights[i] = 1; break;
        }
    }
    for(auto &it : weights) {
        std::cout << it << "\n";
    }

    _graph g{edges.begin(), edges.end(), weights.begin(), 7};

    boost::array<int, 12> predecessors;
    boost::dijkstra_shortest_paths(g, Netherlands, boost::predecessor_map(predecessors.begin()));

    std::cout << "Cheapest path from " << name[Italy ]<< " to " << name[Netherlands] << std::endl;
    int p = Italy;
    while (p != Netherlands)
    {
      std::cout << name[p] << '\n';
      p = predecessors[p];
    }
    std::cout << name[p] << '\n';

//    write_graphviz(std::cout, g, boost::make_label_writer(name));
    return 0;
}
