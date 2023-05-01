#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

class Graph
{
public:
    /**
     * Node structure for use in our Graph class
     * @param name string of the Boss name
     * @param time time it takes to complete boss (node weight)
     * @param related map<Node *, double> that stores each node's edges and the edge weights - acts as our "adjacency list"
     */
    struct Node
    {
        string name;
        double time = 0;
        map<Node *, double> related;

        Node* prereq = NULL;
        int shard_bearer_prereq = 0; // ONLY for godfrey golden shade
    };

    /**
     * Default constructor for our Graph class
     */
    Graph(); // default constructor

    /**
     * Parameterized constructor for our Graph class
     * @param nodes_file string path to the file of nodes to be read into the Graph
     * @param prereqs_file string path to the file of each nodes' prerequisites, if any
     */
    Graph(string nodes_file, string prereqs_file);

    /**
     * Destructor for our Graph
     * Frees allocated memory (node pointers)
     */
    ~Graph();

    /**
     * Function performs a breadth-first-search (BFS) traversal of our Graph given a start node.
     * @param start pointer to the starting Node
     * @returns A vector of nodes traversed in order through the BFS
     */
    vector<Node *> BFS(Node *start);

    /**
     * Function that performs Dijkstra's algorithm to find the shortest path through all the nodes given a start node.
     * @param start pointer to the starting Node
     * @returns A vector of nodes containing the path
     */
    vector<Node *> Dijkstra(Node *start);

    /**
     * Function that performs Floyd warshall algorithm to find the shortest distances between every node in the graph
     * @returns A vector of graph nodes
     */
    vector<vector<double>> FloydWarshall();

    /**
     * @todo do we still even need this fxn?
     */
    vector<Node> SSSP(Node start, Node end);

    /**
     * Converts a graph represented as an edge list to an adjacency matrix.
     * NOTE: From our population of the graph structure,
     * since the input file is processed sequentially,
     * nodes and edges are added to the private nodes vector in the correct order to translate to [i][j] matrix.
     *
     * @param nodes our populated Graph of vector<Node *> that represents the graph as an edge list
     * @return a two-dimensional array representing the adjacency matrix. the value at matrix[i][j] represents the weight of an edge between nodes i and j (and INF if no edge exists)
     */
    vector<vector<double>> edgeListToAdjMatrix(const vector<Node *> nodes);

    // @todo visualization function

    // ------ HELPERS ------

    /**
     * Helper function that adds a node to our Graph structure. Called in parameterized constructor.
     * @param name name of the boss
     * @param time time it takes to complete said boss
     */
    void addNode(string name, double time);

    /**
     * Helper function that adds an edge between two nodes in our Graph structure. Called in parameterized constructor.
     * @param name1 name of the first boss
     * @param name2 name of the second boss
     * @param time time to travel from name1 to name2 (edge weight)
     */
    void addEdge(string name1, string name2, double weight);

    /**
     * Helper function that prints our Graph structure.
     * Useful for local testing or sanity-checks.
     */
    void print();

    /**
     * Helper function to get all the nodes in a populated Graph.
     * Used for testing the constructor.
     * @returns vector of pointers to all nodes in the Graph
     */
    vector<Node *> getNodes() { return nodes; };

    void VectorToCSV();

    //Node* minRelative(Node* node);

private:
    // A vector of Node pointers representing our Graph.
    vector<Node *> nodes;
    int shard_bearers_slain = 0;
};