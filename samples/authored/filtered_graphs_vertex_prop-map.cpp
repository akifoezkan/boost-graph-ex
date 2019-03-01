// http://boost.2283326.n4.nabble.com/boost-filtered-graph-filtering-on-vertex-color-if-I-only-had-a-colormap-td4700125.html
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_utility.hpp>

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graphviz.hpp>

#include <iostream>

class VertexType
{
    public:
        static int i;
        std::string name;
        bool prop;

        VertexType() {
            name = "vertex-" + std::to_string(++i);
            prop = (i % 2 == 0);
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


// visitors 
template<class ColorMap>
struct is_white
{
  is_white() {}
  is_white(ColorMap cm) : m_cm(cm)
  {}

  using key_type = typename boost::property_traits<ColorMap>::key_type;

  bool operator()(const key_type& v) const
  {
    return get(m_cm, v) != boost::default_color_type::white_color;
  }

  ColorMap m_cm;
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

    // filter the graph
    auto index_map = boost::get(boost::vertex_index, g);
    auto color_map = boost::make_vector_property_map<boost::default_color_type>(index_map);
 
    using color_map_type = decltype(color_map);
    using edge_predicate = boost::keep_all;
    using vertex_predicate = is_white<color_map_type>;

    color_map[0] = boost::default_color_type::black_color;
    color_map[1] = boost::default_color_type::white_color;
    color_map[2] = boost::default_color_type::black_color;
    color_map[3] = boost::default_color_type::black_color;
    color_map[4] = boost::default_color_type::black_color;

    using filtered_graph_type = boost::filtered_graph<GraphType, edge_predicate, vertex_predicate>;

    filtered_graph_type fg(g, edge_predicate(), vertex_predicate(color_map));

    // print the graph
    std::cout << "graph:" << std::endl;
    boost::print_graph(g, get(&VertexType::name, g));

    std::ofstream file_out("out.dot");
    boost::write_graphviz(file_out, g, 
            make_label_writer(boost::get(&VertexType::name, g)),
            make_label_writer(boost::get(&EdgeType::name, g)));

    // print the vertex filtered graph
    std::cout << "\n\nvertex filtered graph:" << std::endl;
    boost::print_graph(g, get(&VertexType::name, g));

    std::ofstream file_vfilt("vfilt.dot");
    boost::write_graphviz(file_vfilt, fg, 
            make_label_writer(boost::get(&VertexType::name, fg)),
            make_label_writer(boost::get(&EdgeType::name, fg)));
}
