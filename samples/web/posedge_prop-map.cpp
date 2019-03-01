https://gist.github.com/daniel-j-h/ceb53abffa4b3cb3ab37

#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>

#include <boost/range/algorithm/for_each.hpp>

#include <vector>
#include <iostream>
#include <iterator>
#include <utility>


struct VertexProperty { int x = 0; };
struct EdgeProperty { int y = 0; };

using Graph = boost::compressed_sparse_row_graph<boost::directedS, VertexProperty, EdgeProperty>;

using Vertex = typename boost::graph_traits<Graph>::vertex_descriptor;
using Edge = typename boost::graph_traits<Graph>::edge_descriptor;


template <typename EdgePropMap>
struct PosEdge {
  PosEdge() = default;
  PosEdge(EdgePropMap map_) : map(map_) { }

  template <typename Edge>
  bool operator()(const Edge& e) const {
    return get(map, e) >= 0;
  }

  EdgePropMap map;
};


// convenient type-inference helper
template <typename PropMap>
PosEdge<PropMap> makePosEdgePred(PropMap map) {
  return PosEdge<PropMap>(map);
}

// convenient type-inference helper
template <typename G, typename EdgeP>
boost::filtered_graph<G, EdgeP> makeFilteredGraph(G& graph, EdgeP edgePred) {
  return boost::filtered_graph<G, EdgeP>(graph, edgePred);
}

template <typename Graph>
void printEdges(const Graph& g) {
  boost::for_each(edges(g), [&g](const auto& edge) {
    std::cout << "index: " << edge.idx << ", "
              << "source: " << edge.src << ", "
              << "property: " << g[edge].y << std::endl;
  });
}

template <typename Graph>
void printVertices(const Graph& g) {
  boost::for_each(vertices(g), [&g](const auto& vertex) {
    std::cout << "vertex: " << vertex << ", "
              << "property: " << g[vertex].x << std::endl;
  });
}

void filter() {
  std::vector<Vertex> sources{0, 0, 2};
  std::vector<Vertex> targets{1, 2, 1};
  std::vector<EdgeProperty> props{{-10}, {10}, {-20}};

  Graph g(boost::construct_inplace_from_sources_and_targets, sources, targets, props, 3);

  std::cout << "Initial Graph:" << std::endl;
  printVertices(g);
  printEdges(g);

  auto pred = makePosEdgePred(boost::get(&EdgeProperty::y, g));
  auto fg = makeFilteredGraph(g, pred);

  std::cout << "Filtered Graph View:" << std::endl;
  printVertices(fg);
  printEdges(fg);
}


int main() {
  filter();
}
