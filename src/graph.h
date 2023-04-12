#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Graph {
    private:

        struct Node {
            string name;
            double time = 0;
            map<Node, double> related;
        };

        vector<Node> nodes;

    public:
        Graph(); // default constructor

        Graph(string nodes_file, string prereqs_file); // parameterized constructor

        vector<Node> Dijkstra(Node start);

        vector<Node> SSSP(Node start, Node end);

        vector<Node> BFS(Node start);

        // ? Visualization  function ?

        // any other helpers and whatnot

};