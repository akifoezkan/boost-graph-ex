## adjacency_matrix vs _list
https://www.boost.org/doc/libs/1_69_0/libs/graph/doc/adjacency_matrix.html

 * use the adjacency_matrix for dense graphs (E is close to V^2) 
 * use adjacency_list for sparse graphs (E is much smaller than V^2). 

### adjacency_matrix
+ edge insertion and removal is constant time
- memory used is O(V^2)
- traverse out-edges of each vertex (such as breadth-first search) run in O(V^2) time

### adjacency_list
+ memory used is O(V + E)
- traverse out-edges of each vertex (such as breadth-first search) run in  O(V + E) time

## Embedding bundled properties into a property for the subgraphs:
https://www.boost.org/doc/libs/1_69_0/libs/graph/doc/subgraph.html

struct my_vertex { ... };
typedef property<vertex_index_t, std::size_t, my_vertex> vertex_prop;

struct my_edge { ... };
typedef property<edge_index_t, std::size_t, my_edge> edge_prop;

typedef adjacency_list<vecS, listS, undirectedS, vertex_prop, edge_prop> Graph;
typedef subgraph<Graph> Subgraph;

filtered vs subgraph
https://stackoverflow.com/questions/33098559/should-i-use-filtered-graph-or-subgraph-or-something-else
https://stackoverflow.com/questions/30757833/how-does-boostsubgraph-work-can-we-use-filtered-graph
