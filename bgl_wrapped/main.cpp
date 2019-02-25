#include <iostream>
#include "types.hpp"
#include "graph_dag.hpp"

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

// We do not want to have anything related to boost here
int main()
{
    // Create and fill the graph
    dag<VertexTypeBase> g;
    g.gen_rand_graph(10, 23);
    //ex_graph(g);

    std::cout << "graph:" << std::endl;
    g.print_graph();
    g.write_graphviz();
}
