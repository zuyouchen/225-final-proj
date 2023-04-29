#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

class Graph
{
public:
    // Struct representing an individual node or "boss"
    struct Node
    {
        string name;
        double time = 0;
        // NOTE: Need to store a map from node pointer to double because map keys cannot be structs without overloaded operators
        map<Node *, double> related;
    };

    Graph(); // default constructor

    Graph(string nodes_file, string prereqs_file); // parameterized constructor

    ~Graph();

    vector<Node *> Dijkstra(Node *start);

    vector<Node> SSSP(Node start, Node end);

    vector<Node *> BFS(Node *start);

    // ? Visualization  function ?

    // Helper functions for the construction of the graph
    void addNode(string name, double time);

    void addEdge(string name1, string name2, double weight);

    // Print our graph to check we have it populated
    void print();

    // Return our nodes list for testing purposes
    vector<Node *> getNodes() { return nodes; };

private:
    vector<Node *> nodes;
};