/*
 * Bundled Properties:
 * https://stackoverflow.com/questions/51138794/how-to-use-boost-make-label-writer-to-write-edge-properties 
 * http://coliru.stacked-crooked.com/a/64f1d47539ed4773:w
*/


#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>


struct VertexProps { std::string name; };
struct EdgeProps   { std::string name; };
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProps, EdgeProps> Graph;

int main() {
    Graph g(3);
    g[0].name = "one";
    g[1].name = "two";
    g[2].name = "three";
    add_edge(1, 0, {"e1"}, g);
    add_edge(2, 1, {"e2"}, g);
    add_edge(1, 2, {"e3"}, g);
    add_edge(2, 0, {"e4"}, g);

    write_graphviz(std::cout, g,
            make_label_writer(get(&VertexProps::name, g)),
            make_label_writer(get(&EdgeProps::name, g)));
}
