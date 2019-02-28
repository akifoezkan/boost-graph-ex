#include <iostream>
#include "include/types.hpp"
#include "include/graph_dag.hpp"

template<class Graph_t>
void ex_graph(Graph_t &g) {
    Node kernelx("kernX"), kernely("kernY"), kernelz("kernZ"), kernelt("kernT");
    Image im0("im0"), im1("im1"), im2("im2"), im3("im3");
    Scalar var0("var0"); 

    auto im0_v   = g.add_vertex(im0);
    auto kernx_v = g.add_vertex(kernelx);
    auto im1_v   = g.add_vertex(im1);
    auto kerny_v = g.add_vertex(kernely);
    auto im2_v   = g.add_vertex(im2);
    auto kernz_v = g.add_vertex(kernelz);
    auto kernt_v = g.add_vertex(kernelt);
    auto im3_v   = g.add_vertex(im3);
    auto var0_v = g.add_vertex(var0);

    g.add_edge(im0_v, kernx_v);
    g.add_edge(kernx_v, im1_v);
    g.add_edge(im1_v, kerny_v);
    g.add_edge(im1_v, kernz_v);
    g.add_edge(kerny_v, im2_v);
    g.add_edge(kernz_v, im3_v);
    g.add_edge(im3_v, kernt_v);
    g.add_edge(im2_v, kernt_v);
    g.add_edge(var0_v, kernt_v);
}

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

#define GEN_ACYCLIC_GRAPH

// We do not want to have anything related to boost here
int main() {
    // Create and fill out an example graph
#ifndef GEN_ACYCLIC_GRAPH
    dag<VertexTypeBase> g;

    //ex_graph(g);
    g.gen_rand_graph(10, 23);

    //g.detect_cycles();
    g.detect_and_print_back_edges();
#else
    auto g_ptr = generate_acyclic_graph();
    dag<VertexTypeBase> g = *g_ptr;
#endif

    std::cout << "graph:" << std::endl;
    g.print_graph();
    g.write_graphviz();
    std::cout << "\n\n\n";
}
