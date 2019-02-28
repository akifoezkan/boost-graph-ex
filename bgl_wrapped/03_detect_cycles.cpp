#include <iostream>
#include "include/types.hpp"
#include "include/graph_dag.hpp"

#define PRINT_BACK_EDGES

int main() {
    dag<VertexTypeBase> g;
    g.gen_rand_graph(10, 23);

#ifndef PRINT_BACK_EDGES
    g.detect_cycles();
#else
    g.detect_cycles_and_back_edges();
    g.print_back_edges();
#endif

    std::cout << "graph:" << std::endl;
    g.print_graph();
    g.write_graphviz();
    std::cout << "\n\n\n";
}
