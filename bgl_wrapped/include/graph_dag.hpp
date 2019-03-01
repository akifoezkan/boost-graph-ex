#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp> // dfs search
#include <boost/graph/graph_utility.hpp> // print_graph
#include <boost/graph/graphviz.hpp>
#include <random>

#include "types.hpp"
// Vertex { std::string name }
// VertexTask { std::string name }

// ------------------- graphviz custom node writer ----------------------------
template <class NameMap, class TaskMap>
class vertex_writer {
public:
    vertex_writer(NameMap _namem, TaskMap _taskm) : name_m(_namem), task_m(_taskm) {}

    template <class Vertex>
    void operator()(std::ostream& out, const Vertex& v) const {
        auto task = task_m[v];
        out << " [label = " << name_m[v] << ", style = filled, "; 
        switch (task) {
            case VertexTask::Computation:
                out << "shape = circle, fillcolor = orange]";
        
                break;
            case VertexTask::Buffer:
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


// ---------------------- bsf visitors for cycle detection ----------------------
struct cycle_detector_dfs : public boost::dfs_visitor<>
{
  cycle_detector_dfs(bool& has_cycle) : m_has_cycle(has_cycle) { }

  template <class Edge, class Graph>
  void back_edge(Edge, Graph&) { m_has_cycle = true; }
protected:
  bool& m_has_cycle;
};


template<class Edge_t>
struct cycle_detector_with_backedges_dfs : public boost::dfs_visitor<> {
    cycle_detector_with_backedges_dfs(bool& has_cycle_, std::vector<Edge_t>& back_edges_) :
        has_cycle(has_cycle_), back_edges(back_edges_) { }

    template <class Edge, class Graph>
    void back_edge(Edge e, Graph&) {
        has_cycle = true;
        back_edges.push_back(e);
    }

protected:
    bool& has_cycle;
    std::vector<Edge_t>& back_edges;
};


template <class Edge_t>
inline cycle_detector_with_backedges_dfs<Edge_t> make_cycle_dbe(Edge_t e) {
    return cycle_detector_with_backedges_dfs<Edge_t>(e);
}



// --------------------------- wrapper class -------------------------------
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

#include <cstdarg>

template <class VertexType>
class dag
{
    private:
        typedef boost::adjacency_list< 
                boost::listS, boost::vecS, boost::directedS,
                VertexType>
            Graph_t;

        typedef boost::adjacency_list<> _Grapht;

        typedef _Grapht::vertex_descriptor Vertex_t;

        typedef _Grapht::edge_descriptor Edge_t;

    public:
        Graph_t get_graph(){ return g; }

        template <class Vertex>
        Vertex_t add_vertex(Vertex v) {
            return boost::add_vertex(v, g);
        }

        // we can do the error checking and return edge_descriptor
        std::pair<_Grapht::edge_descriptor, bool> add_edge(
                _Grapht::vertex_descriptor src,
                _Grapht::vertex_descriptor dst) {
            return boost::add_edge(src, dst, g);
        }

        // APIs for detecting cycles
        bool detect_cycles();

        bool detect_cycles_and_back_edges();

        bool has_cycle();

        // APIs for printing
        void print_graph();

        void write_graphviz(std::string filename = "out.dot");

        void print_back_edges();

        // Random graph for test
        void gen_rand_graph(unsigned nvertex, unsigned nedges);

    private:
        Graph_t g;

        bool cycle_exist = false;

        std::vector<Edge_t> back_edges;
};


// ------------------------- filling out the graph -----------------------------


// ------------------ class methods for detecting cycles -----------------------
template <class VertexType>
bool dag<VertexType>::detect_cycles() {
    cycle_detector_dfs vis(cycle_exist);
    depth_first_search(g, visitor(vis));

    if (cycle_exist) {
        std::cout << "The graph has a cycle " << std::endl;
    }

    return cycle_exist;
}


template <class VertexType>
bool dag<VertexType>::detect_cycles_and_back_edges() {
    cycle_detector_with_backedges_dfs<Edge_t> vis(cycle_exist, back_edges);
    depth_first_search(g, visitor(vis));
    return cycle_exist;
}


template <class VertexType>
bool dag<VertexType>::has_cycle() { return cycle_exist; }


// ------------------ class methods for printing -------------------------------
template <class VertexType>
void dag<VertexType>::print_graph() {
    boost::print_graph(g, get(&VertexType::name, g));
}


template <class VertexType>
void dag<VertexType>::write_graphviz(std::string filename) {
    std::ofstream file_out(filename);
    boost::write_graphviz(file_out, g,
            make_vertex_writer(boost::get(&VertexType::name, g),
                boost::get(&VertexType::task, g)));
}

template <class VertexType>
void dag<VertexType>::print_back_edges() {
    if (cycle_exist) {
        std::cout << "Edges at the cycles" << std::endl;
        for(auto it = begin(back_edges); it != end(back_edges); it++) {
           std::cout << g[source(*it, g)].name << " --> "
                     << g[target(*it, g)].name << std::endl;
        }
        std::cout << "\n";
    }
}


// ------------------- random graph generation ---------------------------------
template <class VertexType>
void dag<VertexType>::gen_rand_graph(unsigned n, unsigned k) {
    std::random_device rd;
    std::mt19937 gen(rd());
     std::uniform_int_distribution<> dis(0, n - 1);

    _Grapht::vertex_descriptor images[n];
    _Grapht::vertex_descriptor nodes[n];

    for (unsigned v = 0; v < n; v++ ) {
        auto new_node  = new Node("vertex" + std::to_string(v));
        auto new_image = new Image("image" + std::to_string(v));
        nodes[v] = add_vertex(*new_node);
        images[v] = add_vertex(*new_image);
    }

    // first and last images are not virtual
    g[images[0]].virt = false;
    g[images[n-1]].virt = false;
    add_edge(images[0], nodes[dis(gen)]);
    add_edge(nodes[dis(gen)], images[n-1]);

    for (unsigned i = 0; i < k; i++ ) {
        unsigned u = dis(gen); //rand() % n;
        unsigned v = dis(gen); //rand() % n;
        if (i % 2)
            add_edge(images[u], nodes[v]);
        else
            add_edge(nodes[v], images[v]);
    }
}