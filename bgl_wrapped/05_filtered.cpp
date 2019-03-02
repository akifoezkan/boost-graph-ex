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

template<class G>
void dump_dag_graph(G &g, std::string graph_name = "graph"){
    std::cout << graph_name << std::endl;
    g.print_graph();
    g.write_graphviz(graph_name + ".dot");
    std::cout << "\n\n";

}

template<class VertexType, class G>
void dump_graph(G &g, std::string graph_name = "graph"){
    std::cout << graph_name << std::endl;
    boost::print_graph(g, get(&VertexType::name, g));
    std::cout << "\n\n";

    std::ofstream file_out(graph_name + ".dot");
    boost::write_graphviz(file_out, g, make_label_writer(boost::get(&VertexType::name, g)));

}

int main() {
    auto g_ptr = generate_acyclic_graph();
    dag<VertexTypeBase> g = *g_ptr;

    g.get_space_graph();
    auto g_spaces = *g.spaces_graph;
   
    dump_dag_graph(g);
    dump_graph<VertexTypeBase>(g_spaces, "g_spaces");
}
