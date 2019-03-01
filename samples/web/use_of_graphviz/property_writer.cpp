/* 
 * https://www.boost.org/doc/libs/1_65_0/libs/graph/doc/write-graphviz.html
 * You can write your own PropertyWriter
*/

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iostream>


enum countries { Netherlands, Belgium, France, Germany, Switzerland, Austria, Italy };

template <typename Arry, class Graph>
struct sample_edge_writer {
private:
    Arry value;
    Graph graph;
public:
    sample_edge_writer(Arry _value, Graph _graph) : value(_value), graph(_graph) {}

    template <class Edge>
    void operator()(std::ostream& out, Edge e) const {
        out << "[label = " << value[boost::target(e, graph)] << "]";
    }
};

int main()
{
    const char* name[] = {"Netherlands", "Belgium", "France", "Germany", "Switzerland", "Austria", "Italy"};

    std::array<int, 7> fees = {{0}};
    fees[Germany] = 20;
    fees[France]  = 10;
    fees[Belgium] = 15;

    std::array<std::pair<int, int>, 24> edges{{
      std::make_pair(Netherlands, Belgium),
      std::make_pair(Netherlands, Germany),
      std::make_pair(Belgium,     France),
      std::make_pair(Belgium,     Germany),
      std::make_pair(Germany,     France),
      std::make_pair(Germany,     Austria),
      std::make_pair(Germany,     Switzerland),
      std::make_pair(Switzerland, Italy),
      std::make_pair(Switzerland, France),
      std::make_pair(Switzerland, Austria),
      std::make_pair(Italy,       France),
      std::make_pair(Italy,       Austria),
      std::make_pair(Belgium    , Netherlands),
      std::make_pair(Germany    , Netherlands),
      std::make_pair(France     , Belgium    ),
      std::make_pair(Germany    , Belgium    ),
      std::make_pair(France     , Germany    ),
      std::make_pair(Austria    , Germany    ),
      std::make_pair(Switzerland, Germany    ),
      std::make_pair(Italy      , Switzerland),
      std::make_pair(France     , Switzerland),
      std::make_pair(Austria    , Switzerland),
      std::make_pair(France     , Italy      ),
      std::make_pair(Austria    , Italy      ),
    }};

    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::bidirectionalS,
        boost::no_property, boost::property<boost::edge_weight_t, int>> _graph;

    std::array<int, 24> weights{};

    for(size_t i = 0; i < edges.size(); i++) {
        switch(edges[i].second) {
            case France : weights[i] = 10; break;
            case Belgium: weights[i] = 15; break;
            case Germany: weights[i] = 20; break;
            default: weights[i] = 1; break;
        }
    }

    _graph g{edges.begin(), edges.end(), weights.begin(), 7};

    write_graphviz(std::cout, g, boost::make_label_writer(name), 
        sample_edge_writer<std::array<int, 7>, _graph>(fees, g));
    return 0;
}
