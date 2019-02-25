#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>

// Object
enum class ParseVertexType
{
    None,
    Image,
    Scalar,
    Node
};

class ParseVertexTypeBase
{
    public:
        virtual ~ParseVertexTypeBase() = default;

        ParseVertexType type = ParseVertexType::None;
};

class Image: public ParseVertexTypeBase
{
    public:
        Image() {
            type = ParseVertexType::Image;
        };
        virtual ~Image() = default;
};

class Scalar: public ParseVertexTypeBase
{
    public:
        Scalar() {
            type = ParseVertexType::Scalar;
        };
        virtual ~Scalar() = default;
};

class Node: public ParseVertexTypeBase
{
    public:
        Node() {
            type = ParseVertexType::Node;
        };
        virtual ~Node() = default;
};

typedef boost::adjacency_list<
        boost::listS, boost::vecS, boost::directedS,
        ParseVertexTypeBase>
    ParseGraph_t;

int main()
{
    const std::string names[4] = {"im0", "var0", "kern", "out0"};

    // Instantiate a graph
    ParseGraph_t g;

    // Create data objects first
    Node kernelx, kernely; 
    Image im0, im1, im2, im3;
    Scalar var0, var1; 

    // Fill the graph
    boost::adjacency_list<>::vertex_descriptor im0_v = boost::add_vertex(im0, g);
    auto var0_v = boost::add_vertex(var0, g);
    auto kern_v = boost::add_vertex(kernely, g);
    auto out0_v= boost::add_vertex(kernely, g);

    add_edge(im0_v, kern_v, g);
    add_edge(var0_v, kern_v, g);
    add_edge(kern_v, out0_v, g);

    std::cout << "graph:" << std::endl;
    print_graph(g, names);

    std::ofstream file_out("out.dot");
    write_graphviz(file_out, g, boost::make_label_writer(names));
}
