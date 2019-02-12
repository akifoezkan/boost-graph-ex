/* 
 * https://theboostcpplibraries.com/boost.graph-algorithms
 * Create a graph with vertices for the following countries: Netherlands,
 * Belgium, France, Germany, Switzerland, Austria and Italy. Connect the
 * vertices of those countries with common borders. Find the shortest path –
 * the path with fewest border crossings – to get from Italy to the
 * Netherlands. Write the names of all countries to standard output which you
 * cross on your way from Italy to the Netherlands.
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iostream>

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS> _graph;

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

    _graph g{edges.begin(), edges.end(), 7};

    boost::array<int, 12> predecessors;
    boost::breadth_first_search(g, Netherlands, boost::visitor(boost::make_bfs_visitor(
        boost::record_predecessors(predecessors.begin(), boost::on_tree_edge{}))));

    std::cout << "Shortest path from " << name[Italy ]<< " to " << name[Netherlands] << std::endl;
    int p = Italy;
    while (p != Netherlands)
    {
      std::cout << name[p] << '\n';
      p = predecessors[p];
    }
    std::cout << name[p] << '\n';

    //write_graphviz(std::cout, g, boost::make_label_writer(name));
    return 0;
}
