#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/transpose_graph.hpp>
#include <boost/graph/depth_first_search.hpp>

#include <iostream>

// Here we create a filtered graph based on vertex property.
// We get all the edges that are connected to the filtered vertexes

class VertexType
{
    public:
        static int i;
        std::string name;
        bool prop;
        bool alive = false;

        VertexType() {
            name = "vertex-" + std::to_string(++i);
            prop = (i % 2 == 1);
        };

    private:
};

class EdgeType
{
    public:
        static int i;
        std::string name;
        bool prop;

    public:
        EdgeType() {
            name = "edge-" + std::to_string(++i);
            prop = (i % 3 > 0);
        };
};

int VertexType::i = 0;
int EdgeType::i = 0;


template<class G>
void dump_graph(G &g, std::string graph_name = "graph"){
    std::cout << graph_name << std::endl;
    boost::print_graph(g, get(&VertexType::name, g));
    std::cout << "\n\n";

    std::ofstream file_out(graph_name + ".dot");
    boost::write_graphviz(file_out, g, 
            make_label_writer(boost::get(&VertexType::name, g)),
            make_label_writer(boost::get(&EdgeType::name, g)));

}

// dfs visitor
template<class GraphType>
struct mark_as_alive: public boost::dfs_visitor<>
{
  mark_as_alive() { }
  mark_as_alive(GraphType& g_) : g(g_){ }

//  template <class Edge, class Graph>
//  void forward_or_cross_edge(Edge, Graph&) { m_has_cycle = true; }

    template <class Vertex, class Graph>
    void discover_vertex(Vertex v, Graph&) { g[v].alive = true; }; //g[v].alive = true; }

//    template <class Vertex, class Graph>
//    void start_vertex(Vertex v, Graph&) { g[v].alive = true; }

    private:
    GraphType& g;
};

struct terminator {
    template<class Vertex, class Graph>
    bool operator()(const Vertex& v, const Graph& g) {
        return v == boost::vertex(0, g);
    }
};


int main() {
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
                                  VertexType, EdgeType> GraphType;
    GraphType g(5);

    add_edge(0, 1, g);
    add_edge(0, 2, g);
    add_edge(2, 3, g);
    add_edge(2, 4, g);
    add_edge(3, 1, g);
    //add_edge(4, 2, g);

    GraphType g_transposed;
    boost::transpose_graph(g, g_transposed);

    GraphType::vertex_descriptor root_vertex_descriptor = boost::vertex(1, g);
    mark_as_alive<GraphType> vis(g);

    // --- iterator_property_map is the fastest, but needs to know the size before
    auto index_map = boost::get(boost::vertex_index, g);
    // -- color-map way-0
    // auto color_map = boost::make_vector_property_map<boost::default_color_type>(index_map);

    // -- color-map way-1
    std::vector<boost::default_color_type> colors(boost::num_vertices(g));
    auto color_map = boost::make_iterator_property_map(colors.begin(), index_map);

    boost::depth_first_visit(g_transposed, root_vertex_descriptor, 
            vis, color_map, terminator());

    // filtered graph
    using Predicate = std::function<bool(GraphType::vertex_descriptor)>;
    using Filtered  = boost::filtered_graph<GraphType, boost::keep_all, Predicate>;

    auto is_alive = [&g](GraphType::vertex_descriptor vd) { return g[vd].alive; };
    Filtered g_optimized(g_transposed, boost::keep_all{}, is_alive);
   
    // print functions
    dump_graph(g);
    dump_graph(g_transposed, "transposed");
    dump_graph(g_optimized, "optimized");
}
