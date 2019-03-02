// https://stackoverflow.com/questions/48011373/need-to-find-sub-graphs-from-one-big-graph-using-boostgraph

#include <boost/graph/adjacency_list.hpp>

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, boost::property<boost::vertex_name_t, std::string> >;
using ComponentId = int;
using Mappings    = std::vector<ComponentId>;
using Graphs      = std::vector<Graph>;

Graph build();
Mappings map_components(Graph const&);
Graphs split(Graph const&, Mappings const&);

#include <boost/graph/graph_utility.hpp>
int main() {
    Graph g = build();

    Mappings components = map_components(g);

    for (auto& sub : split(g, components)) {
        std::cout << "\n========================\n";
        print_graph(sub, get(boost::vertex_name, sub));
    }
}

using Vertex = Graph::vertex_descriptor;

Graph build() {
    Graph g;

    Vertex PH = add_vertex({"PH"}, g);
    Vertex PH1 = add_vertex({"PH1"}, g);
    Vertex PH2 = add_vertex({"PH2"}, g);
    Vertex N1 = add_vertex({"N1"}, g);
    Vertex N2 = add_vertex({"N2"}, g);
    Vertex N3 = add_vertex({"N3"}, g);
    Vertex N4 = add_vertex({"N4"}, g);

    add_edge(PH, PH1, g);
    add_edge(PH, PH2, g);
    add_edge(PH1, N1, g);
    add_edge(PH1, N2, g);
    add_edge(PH2, N3, g);
    add_edge(PH2, N4, g);
    return g;
}

#include <boost/graph/biconnected_components.hpp> // articulation_points
#include <boost/graph/connected_components.hpp> // connected_components
#include <boost/graph/filtered_graph.hpp>
#include <boost/function.hpp>

using Filtered = boost::filtered_graph<Graph, boost::keep_all, boost::function<bool(Vertex)> >;

Mappings map_components(Graph const& g) {
    Mappings mappings(num_vertices(g));

    std::vector<Vertex> ap;
    articulation_points(g, back_inserter(ap));

    if (!ap.empty()) {
        // get the articulation point with the lowest degree
        nth_element(ap.begin(), ap.begin()+1, ap.end(), [&](Vertex a, Vertex b) { return degree(a, g) < degree(b, g); });
        Vertex ignored = ap.front();

        std::cout << "Igoring articulation point " << get(boost::vertex_name, g, ignored) << " from graph\n";
        Filtered fg(g, {}, [&](Vertex v) { return ignored != v; });
        
        int num = boost::connected_components(fg, mappings.data());
        mappings[ignored] = num; // make sure the ignored vertex is in its own component
    }
    return mappings;
}

#include <boost/graph/copy.hpp>

Graphs split(Graph const& g, Mappings const& components) {
    if (components.empty())
        return {};

    Graphs results;
        
    auto highest = *std::max_element(components.begin(), components.end());
    for (int c = 0; c <= highest; ++c) {
        results.emplace_back();
        boost::copy_graph(Filtered(g, {}, [c, &components](Vertex v) { return components.at(v) == c; }), results.back());
    }

    return results;
}

