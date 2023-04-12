#include "../src/graph.h"

Graph::Graph() {}

Graph::Graph(string nodes_file, string prereqs_file) {
    // dummy code just to it can compile
    cout << nodes_file << endl;
    cout << prereqs_file << endl;
}

vector<Graph::Node> Graph::Dijkstra(Node start) {
    // dummy code just to it can compile
    vector<Node> to_return;
    to_return.push_back(start);
    return to_return;
}

vector<Graph::Node> Graph::SSSP(Node start, Node end) {
    // dummy code just to it can compile
    vector<Node> to_return;
    to_return.push_back(start);
    to_return.push_back(end);
    return to_return;
}

vector<Graph::Node> Graph::BFS(Node start) {
    // dummy code just to it can compile
    vector<Node> to_return;
    to_return.push_back(start);
    return to_return;
}

// ? Visualization function ?
