#include <iostream>
#include "types.hpp"
#include "graph_dag.hpp"

int main() {
    dag<VertexTypeBase> g;
    g.gen_rand_graph(10, 23);

    //g.detect_cycles();
    g.detect_cycles_and_back_edges();
    g.print_back_edges();

    std::cout << "graph:" << std::endl;
    g.print_graph();
    g.write_graphviz();
    std::cout << "\n\n\n";
}
