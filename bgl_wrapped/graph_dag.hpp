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