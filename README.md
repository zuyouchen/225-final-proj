# CS 225 Final Project: Elden Ring Speedrun Optimizer
Final Project for CS 225 in Spring 2023, created by Malcolm Kaplan, Evan Chen, Tyler Cushing, Numair Hajyani, and Gyury Lee. 

## File Organization

### ```\```
Project configuration files and project reports (README.md, results.md, a link to the presentation, Makefile, contract.md, proposal.md, etc).
### ```\data```
Contains all the input files. Includes a small test csv of nodes and one of prereqs, as well as our actual Elden Ring node csv and prerequisite csv.
### ```\output```
This folder includes all three output files: allrem-output.csv, anypercent-output.csv, and bfs-output.csv, corresponding to the outputs of our three primary path finding algorithms. These files are updated to reflect the path that our traversal takes after running ./bin/exec.
### ```\entry```
Includes our two entry points for the program: the main exec file and the test file.
### ```\src```
Includes our graph.cpp and graph.h files, which define the node structure, the graph structure, and all of our algorithms run on the graph (BFS, Dijkstra's, Floyd-Warshall, and helper methods to read data in, add nodes and edges, etc. Basically everything except the visualization code is present here).

## Installation

1) Set-up the CS 225 Docker environment. Instructions can be found [here](https://courses.engr.illinois.edu/cs225/sp2023/resources/own-machine/). Place the Docker file in the root directory of the project (make sure your Docker environment is running before opening this folder).

2) Clone the respository into a folder within the CS 225 Docker environment.

```bash
git clone https://github.com/zuyouchen/225-final-proj.git
```

3) All files are present upon cloning. We are using MAKE rather than CMAKE, so you need not create a build folder or anything like that.

## Running the Program, Part 1: Calculating the Paths

1) Open a bash terminal

2) To run the program normally, type

```bash
make exec
```

and then 

```bash
./bin/exec
```

Due to our data set being a fixed set of nodes, we do not allow the user to change the input flle. Furthermore, because of our integration into a visualization program, we have enforced the output of our data into the directory `\output`. After making and running `./bin/exec`, we expect all three output files for our primary path finding algorithms ("allrem-output.csv," "anypercent-output.csv," and "bfs-output.csv") are located in the `\output` directory.

3) To run our test suite, type

```bash
make tests
```

and then

```bash
./bin/tests
```

The test suite provides comprehensive checks for all major and minor methods within our program. Each individual test method corresponds to one single method in our main program (BFS, Dijkstra's, addEdge, etc).

## Running the Program, Part 2: Visualizing the Results
1) Navigate through your filessystem to the project directory

2) Look for the folder labeled `Visualization`, open it up, and drag all of the files onto your desktop

3) Run the file labeled `RUN ME RUN ME RUN ME!`, it should be a batch file that opens up a command line, which then opens a GUI

4) After the GUI is opened, select browse

5) Once again, naviagate to the project directory, and select the output you wish to visualize (should be a CSV!!)

6) After you found the file you want to visualize, select open (the bottom rightmost button of the file explorer window that popped up after you hit "Browse")

7) Finally, select OK, and observe


## Input and Outputs for Each Method

`Graph(string nodes_files, string prereqs_file)` - Graph Constructor. Takes in a string as the node file and a string as the prerequisite file. Both can be obtained by copying the path from the csv files in the "data" folder. Does not return anything, but the vector nodes is now populated and each node has its correct data. <br>

`~Graph()` - Destructor for our Graph. Frees allocated memory (pointers to nodes in our Graph). <br>

`void addNode(string name, double time)` - Helper function used to populate our graph. Adds a node given its name and time to complete. Called in constructor. <br>

`void addEdge(string name1, string name2, double weight)` - Helper function used to populate our graph. Adds an edge given two nodes and the weight of said edge. Called in constructor. <br>

`vector<Node *> BFS(Node* start)` - Takes in a starting node, optimally nodes[0], aka "firstStep." Returns a vector of nodes as the path in order of our BFS. Call vectorToCSV and pass in this return value to output a CSV of the path result. <br>

`Dijkstra(Node* start, route r)` - Takes in a starting node, optimally node[0], aka "firstStep," and a route enum, either "allremembrances" (to hit all nodes) or "anypercent" to hit only required nodes to enter the final boss node and finish the game ("radagonAndEldenBeast"). Returns a vector of nodes as the path in order of our shortest path algorithm. Once again, call vectorToCSV and pass in this return value to output a CSV of the path result. <br>

`vector<vector<double>> FloydWarshall()` - Has no parameters. Returns a 2D vector of doubles, corresponding to the shortest distances between every pair of nodes in the graph, via the FloydWarshall algorithm. Not outputted to any location, purely used for testing and understanding routes. <br>

`vector<vector<double>> edgeListToAdjMatrix(const vector<Node *> nodes)` - Takes in our vector of Graph nodes. Converts our constructed Graph (edge list) to an adjacency matrix for usage in FloydWarshall algorithm. Returns a 2D vector of doubles representing the adjacency matrix of the graph.  <br>

`void print()` - Assumes our graph is populated. Prints our edge list graph structure to cout. <br>

`vector<Node *> getNodes()` - Assumes our graph is populated. Getter for the nodes of our Graph (edge list). <br>

`void VectorToCSV(vector<Node *> input, string output, time_returned type)` - Prints our path output from Dijkstra's or BFS to a CSV. Takes in the vector<Node* > path as `input`, a filepath `output`, and a enum type of time we are outputting (BFS, All Remembrances Route, or Any% route). <br>

`bool shouldSkipInAnypercent(Node * node)` - Helper function that determines if we should traverse a route in an any% run. Returns `true` if we should traverse, `false` if we shouldn't. <br>

`double computeTimeViaPath(vector<Node *> path)` - Given a path as input, computes the traversal time this path would take. Called after we calculate best paths for any%, allRem routes so that we can understand the time it takes for said path. <br>

`Node* nameToNode(string bossName)` - Takes in a bossName and returns the pointer to said boss (node) in our graph structure. Helper function used to answer our APSP problem, called in `shortestTimeBetween()`. <br>

`size_t getNodeIdx(Node * node)` - Takes in a node and finds it's numeric index in our vector of nodes. Helper function used to answer our APSP problem, called in `shortestTimeBetween()`. Needed because our FloydWarshall outputs a 2D vector that we need to index to find shortest-path distance values. <br>

`double shortestTimeBetween(string bossA, string bossB)` - Answers our APSP by running FloydWarshall. Takes in two boss names as strings (case sensitive to our data in `nodes.csv`).  Returns the shortest path time between said two bosses, or `-1` if such a path does not exist. Calls `nameToNode()` and `getNodeIdx()`.  <br>

