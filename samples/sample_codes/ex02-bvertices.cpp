/*
 * Example 31.2. Accessing vertices with boost::vertices()
 * https://theboostcpplibraries.com/boost.graph-vertices-and-edges#ex.graph_01
*/

#include <boost/graph/adjacency_list.hpp>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>

//  In this case, boost::adjacency_list::vertex_descriptor is a type definition 
//  for std::size_t, which is not always the case

int main()
{
  boost::adjacency_list<> g;

  boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);
  boost::add_vertex(g);

  std::pair<boost::adjacency_list<>::vertex_iterator,
    boost::adjacency_list<>::vertex_iterator> vs = boost::vertices(g);

  std::copy(vs.first, vs.second,
    std::ostream_iterator<boost::adjacency_list<>::vertex_descriptor>{
      std::cout, "\n"});
}
