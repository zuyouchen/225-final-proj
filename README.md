# CS 225 Final Project: Elden Ring Speedrun Optimizer
Final Project for CS 225 in Spring 2023, created by Malcolm Kaplan, Evan Chen, Tyler Cushing, Numair Hajyani, and Gyury Lee. 

## File Organization

### ```\```
Project configuration files and project reports (README.md, Makefile, contract.md, proposal.md, etc).
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

Due to our data set being a fixed set of nodes, we do not allow the user to change the input flle. Furthermore, because of our integration into a visualization program, we have enforced the output of our data into the folder \output. After running ./bin/exec, all three output files for our primary path finding algorithms ("allrem-output.csv," "anypercent-output.csv," and "bfs-output.csv") are located in the \output folder.

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



## Input and Outputs for Each Method

Graph Constructor: Takes in a string as the node file and a string as the prerequisite file. Both can be obtained by copying the path from the csv files in the "data" folder. Does not return anything, but the vector nodes is now populated and each node has its correct data.

BFS: Takes in a starting node, optimally nodes[0], aka "firstStep." Returns a vector of nodes as the path in order of our BFS. Call vectorToCSV and pass in this return value to output a CSV.

Dijkstra's: Takes in a starting node, optimally node[0], aka "firstStep," and a route enum, either "allremembrances" (to hit all nodes) or "anypercent" to hit only required nodes to enter the final boss node and finish the game ("radagonAndEldenBeast"). Returns a vector of nodes as the path in order of our shortest path algorithm. Once again, call vectorToCSV and pass in this return value to output a CSV.

Floyd-Warshall: Has no parameters. Returns a 2D vector of doubles, corresponding to the distances between every pair of nodes in the graph. Not outputted to any location, purely used for testing and understanding routes.

Our visualization is ...


