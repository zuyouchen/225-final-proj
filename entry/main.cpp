#include <iostream>
#include "../src/graph.h"

using namespace std;

int main() {
    cout << "Main function running" << endl;
    Graph g("data/nodes.csv", "data/prereqs.csv");
    // g.print();
    //g.VectorToCSV();
    // Printing out Dijkstra's on FirstStep
    vector<Graph::Node*> nodes = g.getNodes();
    vector<Graph::Node*> test_path = g.Dijkstra(nodes[0]);
    for (auto& node : test_path) {
        cout << node->name << '(' << node->time << ')' <<  " -> " << endl;;
    }
    return 0;
}