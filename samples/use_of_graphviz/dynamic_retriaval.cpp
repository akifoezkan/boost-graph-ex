/*
 * https://stackoverflow.com/questions/45426129/boostwrite-graphviz-how-to-generate-the-graph-horizontally
 *
 * digraph G {
 * dummy=LR;
 * rankdir=LR;
 * tag2 [label=tag2];
 * tag1 [label=tag1];
 * tag1->tag2  [label=symbol];
 * }
 *
 */

#include <boost/graph/adj_list_serialize.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/property_map/function_property_map.hpp>


using namespace boost;

struct VertexP { std::string tag; };
struct EdgeP { std::string symbol; };
struct GraphP { std::string orientation; };

typedef adjacency_list<vecS, vecS, directedS, VertexP, EdgeP, GraphP> Graph;

int main() {
    Graph g(GraphP{"LR"});
    // Then fill the graph
    add_edge(
        add_vertex(VertexP{ "tag1" }, g),
        add_vertex(VertexP{ "tag2" }, g),
        EdgeP{ "symbol" }, g
    );

    {
        // std::ofstream dot_file("automaton.dot");
        dynamic_properties dp;
        dp.property("node_id", get(&VertexP::tag, g));
        dp.property("label", get(&VertexP::tag, g));
        dp.property("label", get(&EdgeP::symbol, g));
        dp.property("rankdir", boost::make_constant_property<Graph*>(std::string("LR")));
        dp.property("dummy", boost::make_function_property_map<Graph*>([](Graph const* g) { return g->m_property->orientation; }));

        write_graphviz_dp(std::cout, g, dp);
    }
}
