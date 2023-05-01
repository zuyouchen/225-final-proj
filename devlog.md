## Dev Log 
Broken down by individual work, based mainly off commits to this repository and Discord activity.

### Malcolm Kaplan
3/17: Added CSV containing graph data (each row is a node its edges alongside weights for both)
4/12: Setup basic project directories and executables (main, tests)
4/26: Implemented Breadth-First-Search (`Graph::BFS()`) and tests for it
4/29: Wrote function to convert path to a CSV, `Graph::VectorToCSV()`, intended for input to the visualization
4/30: Tinkered with consideration of prerequisite nodes and debugging Dijkstra's
5/1: More debugging Dijkstra's, implemented time counts for type of run (any%, all bosses) given path from Dijkstra's

### Evan Chen
4/12: Developed basic graph structure through functions `Graph::addEdge()`, `Graph::addNode()`. Confirmed functionality through function `Graph::print()`.
4/22: Added basic tests for graph population
4/29: Added documentation to each function in `Graph.h`, modified existing MD files to pivot to Floyd-Warshall for one of our deliverables, wrote function that converts our edge list to an adjacency matrix (`Graph::edgeListToAdjMatrix()`)
4/30: Debugging Dijkstra's (was not hitting all nodes), in collab. with Malcolm's work

### Tyler Cushing
4/24 - 5/1: Developed interactive visualization in Python that takes in our CSV route and displays it on top of an Elden Ring map
4/24 - 5/1: Writing Bash script to setup Python dependencies and run the visualization

### Numair Hajyani
4/29: Wrote `Graph::Dijkstra()` that finds the shortest path through our graph given a start node, also added basic tests for Dijkstra's
4/30: Modified multiple testcases
5/1: Assisted Malcolm in Dijkstra's debugging

### Gyury Lee
4/29: Wrote Floyd Warshall algorithm `Graph::FloydWarshall()` using the conversion to adjacency matrix. Note: Numair's laptop was used to make the changes / commit, but Gyury did this work