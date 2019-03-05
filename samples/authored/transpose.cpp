#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/transpose_graph.hpp>

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



int main() {
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS,
                                  VertexType, EdgeType> GraphType;
    GraphType g(5);

    add_edge(0, 1, g);
    add_edge(0, 2, g);
    add_edge(2, 3, g);
    add_edge(2, 4, g);
    add_edge(3, 1, g);
    add_edge(4, 2, g);

    GraphType g_transposed;
    boost::transpose_graph(g, g_transposed);
   
    // print functions
    dump_graph(g);
    dump_graph(g_transposed, "transposed");
}
