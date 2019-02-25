#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp> // print_graph
#include <boost/graph/graphviz.hpp>
#include <boost/property_map/function_property_map.hpp> //dynmaic properties

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
        
        // we can do the error checking and return edge_descriptor
        std::pair<boost::adjacency_list<>::edge_descriptor, bool> add_edge(
                boost::adjacency_list<>::vertex_descriptor src, 
                boost::adjacency_list<>::vertex_descriptor dst) {
            return boost::add_edge(src, dst, g);
        }

        // APIs for print
        void print_graph() { boost::print_graph(g, get(&VertexType::name, g)); };

        void write_graphviz(std::string filename = "out.dot") {
            std::ofstream file_out(filename);
            boost::write_graphviz(file_out, g,
                    make_label_writer(get(&VertexType::name, g)));
        }
};


// Object
enum class ParseVertexType {
    None,
    Image,
    Scalar,
    Node
};

enum class ParseVertexTask {
   None,
   Computation, 
   Buffer
};


ParseVertexTask set_task(ParseVertexType type) {
    switch (type) {
        case ParseVertexType::Image:
        case ParseVertexType::Scalar:
            return ParseVertexTask::Buffer;
        case ParseVertexType::Node:
            return ParseVertexTask::Computation;
        default: 
            return ParseVertexTask::None;
    }
}

class ParseVertexTypeBase
{
    public:
        std::string name;
        ParseVertexTask task;
        ParseVertexType type;

    public:
        ParseVertexTypeBase() : name(""), task(ParseVertexTask::None) { 
            task = set_task(type);
        };

        ParseVertexTypeBase(std::string _name) : name(_name), task(ParseVertexTask::None) { 
            task = set_task(type);
        };

        ParseVertexTypeBase(ParseVertexType _type) : name(""), type(_type) {
            task = set_task(type);
        };

        ParseVertexTypeBase(std::string _name, ParseVertexType _type) : name(_name), type(_type) {
            task = set_task(type);
        };

        virtual ~ParseVertexTypeBase() = default;

        ParseVertexType get_type() { return type; };

        ParseVertexTask get_task() { return task; };

        std::string get_name() { return name; };

        void set_name(std::string _name) { name = _name; };
};

class Image: public ParseVertexTypeBase
{
    public:
        Image() : ParseVertexTypeBase(ParseVertexType::Image) { };

        Image(std::string _name) : ParseVertexTypeBase(_name, ParseVertexType::Image) { };

        virtual ~Image() = default;
};

class Scalar: public ParseVertexTypeBase
{
    public:
        Scalar() : ParseVertexTypeBase(ParseVertexType::Scalar) { };

        Scalar(std::string _name) : ParseVertexTypeBase(_name, ParseVertexType::Scalar) { };

        virtual ~Scalar() = default;
};

class Node: public ParseVertexTypeBase
{
    public:
        Node() : ParseVertexTypeBase(ParseVertexType::Node) { };

        Node(std::string _name) : ParseVertexTypeBase(_name, ParseVertexType::Node) { };

        virtual ~Node() = default;
};



// We do not want to have anything related to boost here
int main()
{
    // Create data objects first
    Node kernelx("kernX"), kernely("kernY"); 
    Image im0("im0"), im1("im1"), im2("im2"), im3("im3");
    Scalar var0("var0"), var1("var1"); 

    // Create and fill the graph
    dag<ParseVertexTypeBase> g;
    
    auto im0_v  = g.add_vertex(im0);
    auto var0_v = g.add_vertex(var0);
    auto kern_v = g.add_vertex(kernely);
    auto out0_v = g.add_vertex(var1);

    g.add_edge(im0_v, kern_v);
    g.add_edge(var0_v, kern_v);
    g.add_edge(kern_v, out0_v);

    std::cout << "graph:" << std::endl;
    g.print_graph();

    g.write_graphviz();
}
