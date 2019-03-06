https://stackoverflow.com/questions/47518846/how-to-find-the-shortest-path-between-two-vertices-in-a-bgl-graph/47521157#47521157
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/random.hpp>
#include <random>
#include <iostream>

using G = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
using V = G::vertex_descriptor;
using E = G::edge_descriptor;

struct my_visitor : boost::default_dijkstra_visitor {
    using base = boost::default_dijkstra_visitor;
    struct done{};

    my_visitor(V vd, size_t& visited) : destination(vd), visited(visited) {}

    void finish_vertex(V v, G const& g) {
        ++visited;

        if (v == destination)
            throw done{};

        base::finish_vertex(v, g);
    }

  private:
    V destination;
    size_t &visited;
};

int main() {
#if 1
    auto seed = 2912287549; // fixed seed for demo
#else
    auto seed = std::random_device{}();
    std::cout << "SEED: " << seed << "\n";
#endif
    std::mt19937 prng { seed };
    G g;
    generate_random_graph(g, 100, 400, prng);
    print_graph(g);

    V start_vertex = prng()%num_vertices(g);
    V end_vertex   = prng()%num_vertices(g);

    size_t visited;
    std::vector<boost::default_color_type> colors(num_vertices(g), boost::default_color_type{});
    std::vector<V>                         _pred(num_vertices(g),   g.null_vertex());
    std::vector<size_t>                    _dist(num_vertices(g),   -1ull);

    my_visitor vis { end_vertex, visited };
    auto predmap = _pred.data(); // interior properties: boost::get(boost::vertex_predecessor, g);
    auto distmap = _dist.data(); // interior properties: boost::get(boost::vertex_distance, g);

    try {
        std::cout << "Searching from #" << start_vertex << " to #" << end_vertex << "...\n";
        boost::dijkstra_shortest_paths(g, start_vertex, 
                boost::visitor(vis).
                color_map(colors.data()).
                distance_map(distmap).
                predecessor_map(predmap).
                weight_map(boost::make_constant_property<E>(1ul))
            );

        std::cout << "No path found\n";
        return 0;
    } catch(my_visitor::done const&) {
        std::cout << "Percentage skipped: " << (100.0*visited/num_vertices(g)) << "%\n";
    }

    size_t distance = distmap[end_vertex];
    std::cout << "Distance from #" << start_vertex << " to #" << end_vertex << ": " << distance << "\n";

    if (distance != size_t(-1)) {
        std::deque<V> path;
        for (V current = end_vertex; 
                current != g.null_vertex() 
                && predmap[current] != current 
                && current != start_vertex;) 
        {
            path.push_front(predmap[current]);
            current = predmap[current];
        }

        std::cout << "Path from #" << start_vertex << " to #" << end_vertex << ": ";
        std::copy(path.begin(), path.end(), std::ostream_iterator<V>(std::cout, ", "));
        std::cout << end_vertex << "\n";
    }
}
