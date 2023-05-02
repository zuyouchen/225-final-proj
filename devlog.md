## Dev Log 
Broken down by individual work, based mainly off commits to this repository and Discord activity.

### Malcolm Kaplan
3/17: Added CSV containing graph data (each row is a node its edges alongside weights for both) <br>
4/12: Setup basic project directories and executables (main, tests) <br>
4/26: Implemented Breadth-First-Search (`Graph::BFS()`) and tests for it <br>
4/29: Wrote function to convert path to a CSV, `Graph::VectorToCSV()`, intended for input to the visualization <br>
4/30: Tinkered with consideration of prerequisite nodes and debugging Dijkstra's <br>
5/1: More debugging Dijkstra's, implemented time counts for type of run (any%, all bosses) given path from Dijkstra's <br>

### Evan Chen
4/12: Developed basic graph structure through functions `Graph::addEdge()`, `Graph::addNode()`. Confirmed functionality through function `Graph::print()`. <br>
4/22: Added basic tests for graph population <br>
4/29: Added documentation to each function in `Graph.h`, modified existing MD files to pivot to Floyd-Warshall for one of our deliverables, wrote function that converts our adjacency list to an adjacency matrix (`Graph::edgeListToAdjMatrix()`) <br>
4/30: Debugging Dijkstra's (was not hitting all nodes), in collab. with Malcolm's work <br>
5/1: Added functions to answer our all-pairs-shortest-path problem. `Graph::shortestTimeBetween()` finds the shortest time path between two bosses given their names. The path times are calculated with the Floyd-Warshall algorithm (`Graph::FloydWarshall()`). Some helper functions made to cleanup code, including `Graph::getNodeIdx()` and `Graph::nameToNode()` <br>

### Tyler Cushing
4/24 - 5/1: Developed interactive visualization in Python that takes in our CSV route and displays it on top of an Elden Ring map <br>
4/24 - 5/1: Writing Bash script to setup Python dependencies and run the visualization <br>

### Numair Hajyani
4/29: Wrote `Graph::Dijkstra()` that finds the shortest path through our graph given a start node, also added basic tests for Dijkstra's <br>
4/30: Modified multiple testcases <br>
5/1: Assisted Malcolm in Dijkstra's debugging <br>
5/1: Debugging `Graph::FloydWarshall()` to ensure that longer paths could be reached (firstStep -> melania, for example) <br>

### Gyury Lee
4/29: Wrote Floyd Warshall algorithm `Graph::FloydWarshall()` using the conversion to adjacency matrix. Note: Numair's laptop was used to make the changes / commit, but Gyury did this work <br>