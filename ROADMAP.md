# boost-graph-ex

Initially I followed the steps suggested here:
https://stackoverflow.com/questions/8812466/using-c-boosts-graph-library/8812758

## Graph Theory Primer

If you are unfamiliar with graph theory or need a refresher, then take a look at boost's Review of Elementary Graph Theory: 
http://www.boost.org/doc/libs/1_69_0/libs/graph/doc/graph_theory_review.html

This primer is helpful in understanding the terminology, how data structures represent graphs (adjacency matrix, adjacency list, etc…), and algorithms (breadth-first search, depth-first search, shortest-path, etc…).

## Sample Code Described in Detail

For sample code for creating graphs that is described in detail, then take a look at the following section of Boris Schäling's online book - The Boost C++ Libraries: 
http://theboostcpplibraries.com/boost.graph-vertices-and-edges

Boris explains how to work with vertices and edges using the adjacenty_list. The code is thoroughly explained so you can understand each example.

### Also check for simple examples:
http://programmingexamples.net/wiki/Boost/BGL

## Understanding adjacency_list Template Parameters

It is important to understand the template parameters for the adjacency_list. For example, do you want a directed or undirected graph? Do you want your graph to contain multiple edges with the same end nodes (i.e. multigraphs)? Performance also comes into play. Boris' book explains some of these, but you will find additional information on using the adjacenty_list here: 
http://www.boost.org/doc/libs/1_69_0/libs/graph/doc/using_adjacency_list.html

## Understanding Property Maps 

https://www.boost.org/doc/libs/1_48_0/libs/property_map/doc/property_map.html

## Using Custom Objects for Vertices, Edges, or Graphs

If you want to use custom objects for the vertices, edges, or even the graph itself, then you will want to use bundled properties. The following links will be helpful for using bundled properties: 
http://www.boost.org/doc/libs/1_69_0/libs/graph/doc/bundles.html

And perhaps this one too for an example: adding custom vertices to a boost graph

## Detecting Circular Dependencies (Cycles)

A helpful link is one that was already provided - boost's File Dependency
Example that shows how to setup a graph of source code files, order them based
on their compilation order (topological sort), determine what files can be
compiled simultaneously, and determine cyclic dependencies: 
http://www.boost.org/doc/libs/1_69_0/libs/graph/doc/file_dependency_example.html


There are multiple ways to detect circular dependencies including:

### Depth-First Search: 

One simple way is by performing a depth-first search and detecting if the
search runs into an already discovered vertex in the current search tree. Here
is an example of detecting cyclic dependencies using boost's depth-first search

### Topological Sort: 
One can also detect cycles using a topological sort. boost provides a
topological_sort algorithm: 
http://www.boost.org/doc/libs/1_69_0/libs/graph/doc/topological_sort.html

A topological sort works on a directed acyclic graph (DAG). If a cyclic graph
is passed in, then an exception is thrown, thus indicating that the graph has a
circular dependency. Topological_sort includes a depth-first search, but also
provides a linear ordering of the vertices. Here is an example: 

### Strongly Connected Components: 

Additionally, finding strongly connected components can indicate whether or not a graph has cycles: 
http://www.personal.kent.edu/~rmuhamma/Algorithms/MyAlgorithms/GraphAlgor/strongComponent.htm

boost's strong_components function computes the strongly connected components of a directed graph using Tarjan's algorithm. 
http://www.boost.org/doc/libs/1_69_0/libs/graph/doc/strong_components.html


### Stability Isues

You should be very careful with removing edges/vertexes, especially when vecS is selected as a container.
These operations often invalidates the pointers including the descriptors.
https://www.boost.org/doc/libs/1_69_0/libs/graph/doc/adjacency_list.html

### Other Links
https://cs.brown.edu/~jwicks/boost/libs/graph/doc/quick_tour.html
http://blog.hostilefork.com/boost-graph-templates-not-crazy/
