## Leading Question 
How can we leverage a graph representation of Elden Ring’s bosses, graph traversal, Dijkstra’s algorithm, and the Floyd-Warhsall algorithm problem to discover optimal speedrunning routes of the game? 
## Major Deliverables
1. **Graph Structure** - We will be representing the Elden Ring map as a weighted and directed graph where the nodes are each particular boss location and the edges are the travel times from boss to boss
2. **Breadth-First-Search Traversal** - To answer the question of the shortest time to complete every boss in the game, we can utilize a BFS to traverse through the graph and visit every node.  
4. **Dijkstra’s** - This is the algorithm we will implement to solve our leading question of the shortest path through all nodes (a 100% speedrun) and the shortest path between any single node and another (SSSP).  
3. **Floyd-Warshall** - We want to know the shortest path's time between any two bosses A and B. So the shortest path time between any pair. This can be interpreted as “splits” of a speedrun. This is essentially an all-pairs-shortest-path problem. We will find this using the Floyd-Warshall algorithm. 
5. **Graph Visualization** - We were looking to take advantage of some of the GUI functionality of Python, such as NumPy, MatPlotLib, and PySimpleGUI to visually represent our graph and highlight the result of our traversals.

## Dataset Acquisition and Processing
- **Data access**: Malcolm is primarily in charge of data acquisition. He is compiling a CSV containing each node that will be represented by our graph structure. He is doing so by exploring the Elden Ring map and noting down important bosses. He is utilizing prior speedruns of the game to populate individual boss node time and personally timing the travel from one node to another (our edges). 

    The node CSV is formatted as follows: node name, time it takes at node, related node, time to traverse, etc
    
    Ex:
    
    firstStep,70,gatefront,80,dectusHaight,120,
    
    Our prerequisite CSV is formatted as follows: node name, prerequisite (as in, a node that must be visited before the current node)
    
    Ex:
    
    radahn,draconicTreeSentinel
    
- **Data format**: The source of our dataset is observation of the popular video game Elden Ring. Through playing the game and observing others playing the game, we have acquired data about the time it takes to complete specific bosses in the game and travel from one boss to another. Our input dataset is a CSV of 56 nodes. We also have another CSV containing a list of the nodes that have prerequisites (nodes that have to be traveled beforehand). We plan to use all the data to answer our preliminary subquestion of the optimal speedrun of all nodes. 
- **Data Correction** To accomplish this, we're going to:  
Ensure each node has a time, ensure each adjacent node also has a time, ensure there are no disconnected nodes (with no edges), and ensure each boss node is represented. We will throw some parsing onto it to double-check inputs are all good (for example, there should be an integer following each node, meaning time) - we can throw exceptions if otherwise. 

- **Data Storage**: Graph itself is a vector (or set) of nodes. Each node stores a double time and a map from node to double (the double here is the edge weights). The traversals check for prereqs using a global set of visited nodes. For a big O storage estimate, we're going to be storing all of the nodes in a vector, and each one of those nodes is going to be storing a map that essentially acts as an "adjacency list." Since the space complexity of a map is always $n$ and we're going to be storing $n$ nodes, we believe that a conservative estimate of our space complexity would be $O(n^2)$.

## Algorithms
**References** 

Paper on Dijkstra’s and SSSP: [https://www.researchgate.net/publication/273264449_Understanding_Dijkstra_Algorithm](https://www.researchgate.net/publication/273264449_Understanding_Dijkstra_Algorithm)

Erikson’s Textbook:
[https://jeffe.cs.illinois.edu/teaching/algorithms/#book](https://www.researchgate.net/publication/273264449_Understanding_Dijkstra_Algorithm)

Floyd-Warshall Section 8.9 of larger paper, section titled "Floyd-Warshall algorithm for all pairs shortest paths": [http://www.ieor.berkeley.edu/~hochbaum/files/ieor266-2014.pdf] (http://www.ieor.berkeley.edu/~hochbaum/files/ieor266-2014.pdf)

**Function Inputs**

- For Dijkstra’s: takes in a starting node of our graph representation, which will always be node “firstStep,” and a route type that will determine if we complete an "any%" route that completes the game by defeating only 2 shard bearers and beating the game, and an "All Remembrances" route, where a player must defeat all 15 primary bosses and then finish the game. 
- For Floyd-Warshall: takes in an adjacency matrix of our graph, which is computed via a function that converts our adjacency list into an adjacency matrix. The adjacency matrix is a two-dimensional array where the value at position (i, j) represents the weight of the edge from node i to node j. If there is no edge between nodes i and j, the value at position (i, j) is infinity.
- For BFS: takes in a starting node, which will always be node “firstStep"
- For Visualization: takes in a CSV of nodes that represents the path we discovered and draws a line through all of them.

**Function Outputs**

Dijkstra’s returns a vector of nodes visited to show the path. 

Floyd-Warshall returns a matrix where the value at position (i, j) represents the shortest path's time between nodes i and j. If there is no path between nodes i and j, the value at position (i, j) is infinity.

The BFS function returns a vector of nodes visited in order of a BFS traversal. 

The visualization function outputs a line drawn on the actual map of Elden Ring that follows our path of nodes in Python.

**Function Efficiency**

Dijkstra’s Algorithm - Using Dijkstra’s algorithm on our dataset will incur a time complexity of O(V^3) where V is the number of vertices in the graph. The V^2 time comes from the traditional requirements of Dijkstra's algorithm, but since we also have a nested for loop to account for prerequisites. Furthermore, at the end of our algorithm, we will require an additional triple nested for loop to determine the total time of our route.

Floyd-Warshall Algorithm - This algorithm is O(V^3), where V is the number of vertices in the graph. This makes it less efficient than Dijkstra's algorithm but it can be used to find the shortest path between all pairs, whereas Dijkstra's algorithm can only be used to find the shortest path between a single pair.

BFS - Since our BFS will need to handle prerequisite nodes, our algorithm will run at worst case O(V^2). 

Visualization - Our visualization will run at O(n^2) time: it reads in the CSV (and thus loops through all n rows), split a row into a list, and then loop through the list.


**Testing Strategy** 

To test our graph representation, we can create a simple graph and use the same functions, testing if nodes and edges are as expected.

To test Dijkstra’s, we can write test cases to assert the amount of total time it takes to traverse the graph via our expected best path. Furthermore, using game knowledge, we can evaluate if the algorithm traversed makes sense given our constraints. We can write test cases where we assert or require that the amount of time should equal.

To test Floyd-Warshall, we can create a simple graph and run our Floyd-Warshall algorithm to check for correct path times. We can also use some smaller examples from our larger graph (ex: nodes that are one or two edges apart) and compare with manual best-path times. 

To test BFS, our algorithm must print out every single node in the correct order.

To test our visualization, we can analyze if the line drawn actually follows the general location of where the nodes are in the actual map. 


## Timeline
Dataset acquisition (already mostly done)

Build CSV file of graph representation (done)
Code the graph representation  
Complete traversal through the graph (BFS) (done)
Code Djikstra’s algorithm  (done)
Code Floyd-Warshall to answer all-pairs-shortest-path (done)
Account for pre-requisites, etc. (done)
Visualize w/ Python  
