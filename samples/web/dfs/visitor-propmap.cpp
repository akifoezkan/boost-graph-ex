#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace boost;

using Graph = adjacency_list<vecS, vecS, directedS>;

Graph make();

struct my_vis : default_dfs_visitor {
    using colormap = std::map<Graph::vertex_descriptor, default_color_type>;
    colormap vertex_coloring;

    template<typename Vertex, typename Graph>
        void discover_vertex(Vertex v, Graph const& g) {
            default_color_type color = vertex_coloring[v];
            (void) color; // suppress unused warning

            default_dfs_visitor::discover_vertex(v,g);
        }
};

int main() {
    Graph const g = make();

    my_vis vis;
    depth_first_search(g, vis, make_assoc_property_map(vis.vertex_coloring));

    for(auto& vc : vis.vertex_coloring)
        std::cout << "vertex " << vc.first << " color " << vc.second << "\n";

    print_graph(g);
}

Graph make() {
    Graph g;
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_edge(0,1,g);
    add_edge(0,2,g);
    add_edge(1,0,g);
    add_edge(2,4,g);
    add_edge(4,3,g);
    add_edge(3,1,g);

    return g;
}
