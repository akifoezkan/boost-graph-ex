/*
 * https://www.boost.org/doc/libs/1_58_0/libs/graph/doc/bundles.html
 * https://stackoverflow.com/questions/3100146/adding-custom-vertices-to-a-boost-graph
 */

#include <iostream>
#include <boost/graph/adjacency_list.hpp>

struct City
{
  std::string name;
  int population;
  std::vector<unsigned> zipcodes;
};

struct Highway
{
  std::string name;
  double miles;
  int speed_limit;
  int lanes;
  bool divided;
};

struct Country {
  std::string name;
  bool use_right;   // Drive on the left or right
  bool use_metric;  // mph or km/h
};

int main()
{

    typedef boost::adjacency_list<
            boost::listS, boost::vecS, boost::bidirectionalS,
            City, Highway, Country>
        Graph_t;

    //Instantiate a graph
    Graph_t g;

    // Fill the graph
    Country USA {"USA", 1, 1}; 

    City california {"California", 1000000, std::vector<unsigned>(91054)};

    auto v0 = add_vertex(g);
    auto v1 = add_vertex(california, g);
    add_edge(v0, v1, g);

    // Vertex properties
    Graph_t::vertex_descriptor v = *vertices(g).first;
    g[v].name = "Troy";
    g[v].population = 49170;
    g[v].zipcodes.push_back(12180);
    // Edge properties
    Graph_t::edge_descriptor e = *out_edges(v, g).first;
    g[e].name = "I-87";
    g[e].miles = 10.;
    g[e].speed_limit = 65;
    g[e].lanes = 4;
    g[e].divided = true;
    // Country properties
    g[boost::graph_bundle].name = "United States";
    g[boost::graph_bundle].use_right = true;
    g[boost::graph_bundle].use_metric = false;
}
