// http://boost.2283326.n4.nabble.com/boost-filtered-graph-filtering-on-vertex-color-if-I-only-had-a-colormap-td4700125.html
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>

#include <boost/property_map/property_map.hpp>

#include <iostream>


// Here we create a filtered graph based on vertex property.
// We get all the edges that are connected to the filtered vertexes

class VertexType
{
    public:
        static int i;
        std::string name;
        bool prop;

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


// visitors 
template<class PropMap>
struct is_prop
{
    is_prop() {}
    is_prop(PropMap cm) : p_map(cm) {}

    template<class VertexOrEdge>
    bool operator()(const VertexOrEdge& v) const
    {
      return p_map[v];
    }

    private:
        PropMap p_map;
};



int main() {
    // graph
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
                                  VertexType, EdgeType> GraphType;
    GraphType g(5);

    add_edge(0, 1, g);
    add_edge(0, 2, g);
    add_edge(2, 3, g);
    add_edge(2, 4, g);
    add_edge(3, 1, g);
    add_edge(4, 2, g);

    // filter the graph according to Vertex
    auto prop_map = boost::get(&VertexType::prop, g);
    using prop_map_type = decltype(prop_map);

    using edge_predicate = boost::keep_all;
    using vertex_predicate = is_prop<prop_map_type>;
    using filtered_graph_type = boost::filtered_graph<GraphType, edge_predicate, vertex_predicate>;

    filtered_graph_type fg_vert(g, edge_predicate(), vertex_predicate(prop_map));

    // filter the graph according to Edge
    using edge_prop_map_type = decltype(boost::get(&EdgeType::prop, g));
    using edge_filtered_graph_type = boost::filtered_graph<GraphType, is_prop<edge_prop_map_type>, boost::keep_all>;

    edge_filtered_graph_type fg_edge(g, is_prop<edge_prop_map_type>(boost::get(&EdgeType::prop, g)), boost::keep_all());

    
    // print graphs
    dump_graph(g);
    dump_graph(fg_vert, "vfilt");
    dump_graph(fg_edge, "efilt");
}
