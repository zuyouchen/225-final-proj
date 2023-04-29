# CS 225 Final Project: Elden Ring Speedrun Optimizer
Final Project for CS 225 in Spring 2023, created by Malcolm Kaplan, Evan Chen, Tyler Cushing, Numair Hajyani, and Gyury Lee. 

## File Organization

* ### ```\```
  Project configuration files (README.md, Makefile, contract.md, proposal.md, etc).
* ### ```\data```
  Contains all the input files. Includes a small test csv of nodes and one of prereqs, as well as our actual Elden Ring node csv and prerequisite csv.
* ### ```\entry```
  Includes our two entry points for the program: the main exec file and the test file.
* ### ```\src```
  Includes our graph.cpp and graph.h files, which define the node structure, the graph structure, and all of our algorithms run on the graph (BFS, Dijkstra's, Floyd-Warshall, and helper methods to read data in, add nodes and edges, etc. Basically everything except the visualization code is present here).

## Installation

1) Set-up the CS 225 Docker environment. Instructions can be found [here](https://courses.engr.illinois.edu/cs225/sp2023/resources/own-machine/). Place the Docker file in the root directory of the project (make sure your Docker environment is running before opening this folder).

2) Clone the respository into a folder within the CS 225 Docker environment.

```bash
git clone https://github.com/zuyouchen/225-final-proj.git
```

3) All files are present upon cloning. We are using MAKE rather than CMAKE, so you need not create a build folder or anything like that.

## Running the Program

1) Open a bash terminal

2) To run the program normally, type

```bash
make exec
```

and then 

```bash
./bin/exec
```

3) To run our test suite, type

```bash
make tests
```

and then

```bash
./bin/tests
```

The test suite provides comprehensive checks for all major and minor methods within our program. Each individual test method corresponds to one single method in our main program (BFS, Dijkstra's, addEdge, etc).

## Input and Outputs for Each Method



