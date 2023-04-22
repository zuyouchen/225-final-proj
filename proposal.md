## Leading Question 
How can we leverage a graph representation of Elden Ring’s bosses, graph traversal, Dijkstra’s algorithm, and the single-source-shortest-path (SSSP) problem to discover optimal speedrunning routes of the game? 
## Major Deliverables
1. **Graph Structure** - We will be representing the Elden Ring map as a weighted and directed graph where the nodes are each particular boss location and the edges are the travel times from boss to boss
2. **Breadth-First-Search Traversal** - To answer the question of the shortest time to complete every boss in the game, we can utilize a BFS to traverse through the graph and visit every node.  
3. **SSSP Problem** - We want to know the shortest path between any two bosses A and B. So the shortest path between any pair. This can be interpreted as “splits” of a speedrun, and is a modified version of SSSP as we are changing the single-source node and calculating all best paths to other nodes  
4. **Dijkstra’s** - This is the algorithm we will implement to solve our leading questions of the shortest path through all nodes and the shortest path between any single node and another (SSSP).  
5. **Graph Visualization** - We were looking to take advantage of some of the GUI functionality of Python, such as NumPy, MatPlotLib, and PySimpleGUI to visually represent our graph and highlight the result of our traversals.

## Dataset Acquisition and Processing
- **Data access**: Malcolm is primarily in charge of data acquisition. He is compiling a CSV containing each node that will be represented by our graph structure. He is doing so by exploring the Elden Ring map and noting down important bosses. He is utilizing prior speedruns of the game to populate individual boss node time and personally timing the travel from one node to another (our edges). 

    The CSV is formatted as follows: node name, time it takes at node, related node, time to traverse, etc
    Ex:
    firstStep, 70, gatefront, 80, dectusHaight, 120,
    
- **Data format**: The source of our dataset is observation of the popular video game Elden Ring. Through playing the game and observing others playing the game, we have acquired data about the time it takes to complete specific bosses in the game and travel from one boss to another. Our input dataset is a CSV of 56 nodes. We also have another CSV containing a list of the nodes that have prerequisites (nodes that have to be traveled beforehand). We plan to use all the data to answer our preliminary subquestion of the optimal speedrun of all nodes. 
- **Data Correction** To accomplish this, we're going to:  
Ensure each node has a time, ensure each adjacent node also has a time, ensure there are no disconnected nodes (with no edges), and ensure each boss node is represented. We will throw some parsing onto it to double-check inputs are all good (for example, there should be an integer following each node, meaning time) - we can throw exceptions if otherwise. 

- **Data Storage**: Graph itself is a vector (or set) of nodes. Each node stores a double time and a map from node to double (the double here is the edge weights). The traversals check for prereqs using a global set of visited nodes. For a big O storage estimate, we're going to be storing all of the nodes in a vector, and each one of those nodes is going to be storing a map that essentially acts as an "adjacency list." Since the space complexity of a map is always $n$ and we're going to be storing $n$ nodes, we believe that a conservative estimate of our space complexity would be $O(n^2)$.

## Algorithms
**References** 

Paper on Dijkstra’s and SSSP: [https://www.researchgate.net/publication/273264449_Understanding_Dijkstra_Algorithm](https://www.researchgate.net/publication/273264449_Understanding_Dijkstra_Algorithm)

Erikson’s Textbook:
[https://jeffe.cs.illinois.edu/teaching/algorithms/#book](https://www.researchgate.net/publication/273264449_Understanding_Dijkstra_Algorithm)

**Function Inputs**

- For Dijkstra’s: takes in a starting node of our graph representation, which will always be node “firstStep,” and the graph’s adjacency list, represented as a vector of nodes
- For SSSP: takes in a starting node and ending node
- For BFS: takes in a starting node, which will always be node “firstStep”
- For Visualization: takes in a vector of nodes and visualizes the best path through all of them

**Function Outputs**

Dijkstra’s and SSSP return a vector of nodes visited to show the path. 

The BFS function returns a vector of nodes visited in order of a BFS traversal. 

The visualization function outputs a line drawn on the actual map of Elden Ring that follows our path of nodes in Python.

**Function Efficiency**

Dijkstra’s Algorithm - Using Dijkstra’s algorithm on our dataset will incur a time complexity of O(V^2) where V is the number of vertices in the graph. 

SSSP - Considering this problem will be solved using Dijkstra's algorithm, it will also take O(V^2) time where V is the number of vertices in the graph.

BFS - implemented properly, BFS should incur a time complexity of O(n) where n is the number of nodes in our graph.

Visualization - Our function will traverse our shortest path using whichever algorithm we want to visualize, so it will either be O(V^2) if we are visualizing Dijkstra's/SSSP or O(n) if we are visualizing BFS.


**Testing Strategy** 

To test Dijkstra’s and SSSP, we can write test cases to assert the amount of total time it takes to traverse the graph via our expected best path. Furthermore, using game knowledge, we can evaluate if the algorithm traversed makes sense given our constraints. We can write test cases where we assert or require that the amount of time should equal.

To test BFS, our algorithm must print out every single node in the correct order.

To test our visualization, we can analyze if the line drawn actually follows the general location of where the nodes are in the actual map. 


## Timeline
Dataset acquisition (already mostly done)

Build CSV file of graph representation  
Code the graph representation  
Complete traversal through the graph (BFS)  
Code Djikstra’s algorithm  
Visualize w/ Python  
Answer the SSSP problem generalized to all node pairs A, B
