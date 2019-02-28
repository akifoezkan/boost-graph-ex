#include <iostream>
#include "include/types.hpp"
#include "include/graph_dag.hpp"

dag<VertexTypeBase>* generate_acyclic_graph(){
    dag<VertexTypeBase> *g_ptr;

    bool has_cycle = true;
    while (has_cycle) {
        std::cout << "Create a new graph" << std::endl;
        g_ptr = new dag<VertexTypeBase>();
        g_ptr->gen_rand_graph(10, 23);
        has_cycle = g_ptr->detect_cycles();
        std::cout << std::endl;
    }

    return g_ptr;
}


int main() {
    auto g_ptr = generate_acyclic_graph();
    dag<VertexTypeBase> g = *g_ptr;

    std::cout << "graph:" << std::endl;
    g.print_graph();
    g.write_graphviz();
    std::cout << "\n\n\n";
}
