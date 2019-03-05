// https://stackoverflow.com/questions/47060794/make-a-subgraph-of-a-boost-graph-by-removing-leaves

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_utility.hpp>

/// vertex properties
struct VertexData {
    std::string label;
    int num;
    bool is_leaf=false;
};

/// edges properties
struct EdgeData {
    std::string edge_name;
    double edge_confidence;
};

/// define the boost-graph
typedef boost::adjacency_list<boost::vecS, boost::vecS,
        boost::bidirectionalS,
        boost::property<boost::vertex_index_t, size_t, VertexData>,
        boost::property<boost::edge_weight_t, double, EdgeData> > Graph;

using Predicate = std::function<bool(Graph::vertex_descriptor)>;
using Filtered  = boost::filtered_graph<Graph, boost::keep_all, Predicate>;

Graph make_graph();

int main() {
    Graph g = make_graph();
    auto const labels = get(&VertexData::label, g);

    std::cout << "\n---Main graph:\n";
    print_graph(g, labels);

    // manual markings
    {
        auto manual_is_leaf = [&g](Graph::vertex_descriptor vd) { return !g[vd].is_leaf; };
        Filtered manual(g, boost::keep_all{}, manual_is_leaf);

        {

            std::cout << "\n---Filtered, no leafs:\n";
            print_graph(manual, labels);
        }

        {
            std::cout << "\n---Filtered, manual leafs:\n";
            g[2].is_leaf = true; // only "three"

            print_graph(manual, labels);
        }
    }

    // automatic, dynamic markings
    {
        // note that for bidirectional/undirected out_degree might not make
        // sense, but neither does the notion of a leaf! 
        auto by_degree = [&g](Graph::vertex_descriptor vd) { return boost::degree(vd, g); };
        Filtered automatic(g, boost::keep_all{}, by_degree);

        {
            std::cout << "\n---Filtered by actual out_degree:\n";
            print_graph(automatic, labels);
        }

        {
            // make `five` and `six` appear:
            add_edge(5, 4, 100, g); // six -> five

            std::cout << "\n---After adding an edge:\n";
            print_graph(automatic, labels);
        }
    }
}

Graph make_graph() {
    Graph g;

    auto v1 = add_vertex({ 1, {"one",   100, false} }, g);
    auto v2 = add_vertex({ 2, {"two",   200, false} }, g);
    auto v3 = add_vertex({ 3, {"three", 300, false} }, g);
    auto v4 = add_vertex({ 4, {"four",  400, false} }, g);
    auto v5 = add_vertex({ 5, {"five",  500, false} }, g);
    auto v6 = add_vertex({ 6, {"six",   600, false} }, g);

    add_edge(v1, v2, 0.5, g);
    add_edge(v2, v3, 0.5, g);
    add_edge(v3, v4, 0.5, g);
    add_edge(v3, v5, 0.5, g);
    add_edge(v3, v6, 0.5, g);
    add_edge(v2, v4, 0.5, g);
    add_edge(v3, v5, 0.5, g);
    add_edge(v4, v6, 0.5, g);

    return g;
}
