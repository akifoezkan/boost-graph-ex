#include <iostream>
#include "types.hpp"
#include "graph_dag.hpp"

int main() {
    dag<VertexTypeBase> g;

    // Number of vertices and edges
    g.gen_rand_graph(10, 23);

    std::cout << "graph:" << std::endl;
    g.print_graph();
    g.write_graphviz();
    std::cout << "\n\n\n";
}
