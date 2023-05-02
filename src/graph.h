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
#include <limits>
using namespace std;

// For giving our visualization a title
enum time_returned
{
    bfs,
    allremtime,
    anypercenttime
};
// For deciding whether Dijkstra's computes an anypercent or an all remembrances run
enum route
{
    allremembrances,
    anypercent
};

class Graph
{
public:
    /**
     * Node structure for use in our Graph class
     * @param name string of the Boss name
     * @param time time it takes to complete boss (node weight)
     * @param related map<Node *, double> that stores each node's edges and the edge weights - acts as our "adjacency list"
     * @param prereq, a node that must be visited before visiting that node; default NULL means no prereqs
     * @param shard_berarer_prereq, how many demigods must be visited before visiting; default 0 means none
     */
    struct Node
    {
        string name;
        double time = 0;
        map<Node *, double> related;

        Node *prereq = NULL;         // null for all but a few nodes, as specifed in prereqs.csv
        int shard_bearer_prereq = 0; // ONLY for godfrey (golden shade)
    };

    /**
     * Default constructor for our Graph class
     */
    Graph();

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
     * @
     */
    vector<Node *> Dijkstra(Node *start, route r);

    /**
     * Function that performs Floyd warshall algorithm to find the shortest distances between every two nodes in the graph
     * @returns A 2D vector of doubles containing the distances between all pairs of nodes
     */
    vector<vector<double>> FloydWarshall();

    /**
     * Converts a graph represented as an adjacency list to an adjacency matrix.
     * NOTE: From our population of the graph structure,
     * since the input file is processed sequentially,
     * nodes and edges are added to the private nodes vector in the correct order to translate to [i][j] matrix.
     *
     * @param our populated Graph of vector<Node *> that represents the graph as an edge list
     * @return a two-dimensional array representing the adjacency matrix. the value at matrix[i][j] represents the weight of an edge between nodes i and j (and INF if no edge exists)
     */
    vector<vector<double>> adjListToAdjMatrix(const vector<Node *> nodes);

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

    /**
     * Helper function to print a vector to a CSV.
     * Used to test and feed into visualization.
     */
    void VectorToCSV(vector<Node *> input, string output, time_returned type);

    /**
     * Helper function to determine if we should traverse a route in the any% run
     * @param a node to check
     * @returns a boolean, "true" for if we should traverse, "false" for if we should skip
     */
    bool shouldSkipInAnypercent(Node *node);

    /**
     * Helper function to compute a total time given a path of nodes
     * @param path a path, composed of node pointers
     * @returns a double, computing the total time in seconds that the run takes
     */
    double computeTimeViaPath(vector<Node *> path);

    /**
     * Function that finds the pointer to a Node in our graph given a name (case-sensitive!)
     * @param bossName string name of a boss
     * @returns a pointer to a node, or NULL if the node does not exist matching the name
     */
    Node *nameToNode(string bossName);

    /**
     * Function that finds the index of a node given a pointer to it
     * @param node pointer to the node
     */
    size_t getNodeIdx(Node *node);

    /**
     * Function that uses the Floyd-Warshall algorithm to output the fastest time it takes to traverse between two nodes (Boss A, Boss B)
     * Answers our All Pairs Shortest Path problem (with only the time)
     *
     * @param bossA first boss name
     * @param bossB second boss name
     * @returns a double, the shortest time between bossA and bossB. returns -1 if either name passed is invalid, or if the path does not exist
     */
    double shortestTimeBetween(string bossA, string bossB);

    /**
     * Helper functions to return the private time variables
     */
    double getBFSTotal() { return BFS_total_time; }
    double getAllRemsTotal() { return all_rem_total_time; }
    double getAnypercentTotal() { return anypercent_total_time; }

private:
    /**
     * Graph is represented as a vector of node structs
     */
    vector<Node *> nodes;

    /**
     * Number of shardbearers (demigods) slain; 2 are required to fight Godfrey (Golden Shade)
     */
    int shard_bearers_slain = 0;

    /**
     * Variables to keep track of our total time for each route
     */
    double BFS_total_time = 0;        // computed by BFS
    double all_rem_total_time = 0;    // computed by Dijkstra's
    double anypercent_total_time = 0; // computed by Dijkstra's
};