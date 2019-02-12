/*
 * Example 31.4. boost::adjacency_list with selectors 
 * https://theboostcpplibraries.com/boost.graph-vertices-and-edges#ex.graph_01
*/

#include <boost/graph/adjacency_list.hpp>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>

#define DIRECTED_GRAPH 0

// * p3: boost::directedS (default) => whether lines are directed or undirected
// * p2: boost::vecS (default)      => which class should be used for points
// * p1: boost::SetS uses std::set (map with a key, so no duplicates)
//       -> std::set is selected as the container for lines.
//          Because std::set doesn’t support duplicates, it is not possible to add 
//          the same line using boost::add_edge() multiple times.

// APIs
// vertex_descriptor, edge_descriptor, edge_iterator
// add_vertex, add_edge

int main()
{
#if DIRECTED_GRAPH == 1
  typedef boost::adjacency_list<> _graph;
#else
  // template parameters: (S)electors
  // boost::SetS uses std::set (map with a key, so no duplicates) for the container
  typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS> _graph;
#endif
  _graph g;

  _graph::vertex_descriptor v1 = boost::add_vertex(g);
  _graph::vertex_descriptor v2 = boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);

  std::pair<_graph::edge_descriptor, bool> p = boost::add_edge(v1, v2, g);
  std::cout.setf(std::ios::boolalpha);
  std::cout << p.second << '\n';

  p = boost::add_edge(v1, v2, g);
  std::cout << p.second << '\n';

  p = boost::add_edge(v2, v1, g);
  std::cout << p.second << '\n';

  std::pair<_graph::edge_iterator, _graph::edge_iterator> es = boost::edges(g);

  std::copy(es.first, es.second, std::ostream_iterator<_graph::edge_descriptor>{std::cout, "\n"});
}
