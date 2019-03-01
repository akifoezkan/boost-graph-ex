/*
 * Bundled Properties:
 * https://stackoverflow.com/questions/51138794/how-to-use-boost-make-label-writer-to-write-edge-properties 
 * http://coliru.stacked-crooked.com/a/cca5ca9d4bbf5a0a 
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

int main() {
    Graph g(3);
    auto e1 = add_edge(1, 0, g).first;
    auto e2 = add_edge(2, 1, g).first;
    auto e3 = add_edge(1, 2, g).first;
    auto e4 = add_edge(2, 0, g).first;

    std::vector<std::string>                      vname{ "one", "two", "three" };
    std::map<Graph::edge_descriptor, std::string> ename{ 
        { e1, "e1" },
        { e2, "e2" },
        { e3, "e3" },
        { e4, "e4" },
    };

    write_graphviz(std::cout, g,
            boost::make_label_writer(&vname[0]),
            make_label_writer(boost::make_assoc_property_map(ename)));
}
