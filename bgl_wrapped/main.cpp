#include <iostream>
#include "types.hpp"
#include "graph_dag.hpp"

// We do not want to have anything related to boost here
int main()
{
    // Create data objects first
    Node kernelx("kernX"), kernely("kernY"); 
    Image im0("im0"), im1("im1"), im2("im2"), im3("im3");
    Scalar var0("var0"), var1("var1"); 

    // Create and fill the graph
    dag<VertexTypeBase> g;

    auto im0_v  = g.add_vertex(im0);
    auto var0_v = g.add_vertex(var0);
    auto kern_v = g.add_vertex(kernely);
    auto out0_v = g.add_vertex(var1);

    g.add_edge(im0_v, kern_v);
    g.add_edge(var0_v, kern_v);
    g.add_edge(kern_v, out0_v);

    std::cout << "graph:" << std::endl;
    g.print_graph();
    g.write_graphviz();
}
