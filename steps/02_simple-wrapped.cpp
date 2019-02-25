#include <iostream>
//#include "simple_dag.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp> // print_graph
#include <boost/graph/graphviz.hpp>
 
//  boost::adjacency_list<
//          OutEdgeList, VertexList, Directed, 
//          VertexProperties, EdgeProperties, GraphProperties, EdgeList > 
//      Graph_type;
//
//  Stability of Iterator Pointers:
//      In general, if you want your vertex and edge descriptors to be stable
//      (never invalidated) then use listS or setS for the VertexList and
//      OutEdgeList template parameters of adjacency_list. If you are not as
//      concerned about descriptor and iterator stability, and are more
//      concerned about memory consumption and graph traversal speed, use vecS
//      for the VertexList and/or OutEdgeList template parameters. 
//  link: https://www.boost.org/doc/libs/1_60_0/libs/graph/doc/adjacency_list.html

template <class VertexType>
class dag
{
    private:

        typedef boost::adjacency_list< 
                boost::listS, boost::vecS, boost::directedS,
                VertexType>
            Graph_t;

        Graph_t g;

    public:
        Graph_t get_graph(){ return g; }
        
        template <class Vertex>
        boost::adjacency_list<>::vertex_descriptor add_vertex(Vertex v) {
            return boost::add_vertex(v, g);
        }
        
        // TODO: we can do the error checking and return edge_descriptor
        std::pair<boost::adjacency_list<>::edge_descriptor, bool> add_edge(
                boost::adjacency_list<>::vertex_descriptor src, 
                boost::adjacency_list<>::vertex_descriptor dst) {
            return boost::add_edge(src, dst, g);
        }

        // APIs for print
        void print_graph() { boost::print_graph(g); };
        
        template<class Name>
        void print_graph(Name name) { boost::print_graph(g, name); };

        void write_graphviz(std::string filename = "out.dot") {
            std::ofstream file_out(filename);
            boost::write_graphviz(file_out, g);
        }

        template<class Name>
        void write_graphviz(Name names, std::string filename = "out.dot") {
            std::ofstream file_out(filename);
            boost::write_graphviz(file_out, g, boost::make_label_writer(names));
        }
};

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
        Image() { type = ParseVertexType::Image;};
        virtual ~Image() = default;
};

class Scalar: public ParseVertexTypeBase
{
    public:
        Scalar() { type = ParseVertexType::Scalar; };
        virtual ~Scalar() = default;
};

class Node: public ParseVertexTypeBase
{
    public:
        Node() { type = ParseVertexType::Node; };
        virtual ~Node() = default;
};



// We do not want to have anything related to boost here
int main()
{
    const std::string names[4] = {"im0", "var0", "kern", "out0"};

    // Create data objects first
    Node kernelx, kernely; 
    Image im0, im1, im2, im3;
    Scalar var0, var1; 

    // Create and fill the graph
    dag<ParseVertexTypeBase> g;
    
    auto im0_v  = g.add_vertex(im0);
    auto var0_v = g.add_vertex(var0);
    auto kern_v = g.add_vertex(kernely);
    auto out0_v = g.add_vertex(kernely);

    g.add_edge(im0_v, kern_v);
    g.add_edge(var0_v, kern_v);
    g.add_edge(kern_v, out0_v);

    std::cout << "graph:" << std::endl;
    g.print_graph(names);

    std::ofstream file_out("out.dot");
    g.write_graphviz(names);
}
