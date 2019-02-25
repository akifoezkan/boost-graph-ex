#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp> // print_graph
#include <boost/graph/graphviz.hpp>
#include <random>


#include "types.hpp"

// graphviz custom node writer
template <class NameMap, class TaskMap>
class vertex_writer {
public:
    vertex_writer(NameMap _namem, TaskMap _taskm) : name_m(_namem), task_m(_taskm) {}

    template <class Vertex>
    void operator()(std::ostream& out, const Vertex& v) const {
        auto task = task_m[v];
        out << " [label = " << name_m[v] << ", style = filled, "; 
        switch (task) {
            case ParseVertexTask::Computation:
                out << "shape = circle, fillcolor = orange]";
        
                break;
            case ParseVertexTask::Buffer:
                out << "shape = box, fillcolor = grey]";
                break;
            default: 
                out << "shape = diamond, fillcolor = red]";;
                break;
        }
    }

private:
    NameMap name_m;
    TaskMap task_m;
};

template <class NameMap, class TaskMap>
inline vertex_writer<NameMap, TaskMap> make_vertex_writer(NameMap nm, TaskMap tm) {
    return vertex_writer<NameMap, TaskMap>(nm, tm);
}

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
                    //make_label_writer(get(&VertexType::name, g)),
                    make_vertex_writer(boost::get(&VertexType::name, g), 
                        boost::get(&VertexType::task, g)));
        }

        // Random graph for test
        void gen_rand_graph(unsigned n, unsigned k) {
            std::random_device rd;
            std::mt19937 gen(rd());
             std::uniform_int_distribution<> dis(0, n - 1);

            boost::adjacency_list<>::vertex_descriptor images[n];
            boost::adjacency_list<>::vertex_descriptor nodes[n];

            for (unsigned v = 0; v < n; v++ ) {
                auto new_node  = new Node("vertex" + std::to_string(v));
                auto new_image = new Image("image" + std::to_string(v));
                nodes[v] = add_vertex(*new_node);
                images[v] = add_vertex(*new_image);
            }

            for (unsigned i = 0; i < k; i++ ) {
                unsigned u = dis(gen); //rand() % n;
                unsigned v = dis(gen); //rand() % n;
                if (i % 2)
                    add_edge(images[u], nodes[v]);
                else
                    add_edge(nodes[v], images[v]);
            }
        }
};
