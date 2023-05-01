#include <iostream>
#include "../src/graph.h"

using namespace std;

int main() {
    cout << "Main function running" << endl;
    Graph g("data/nodes.csv", "data/prereqs.csv");
    // g.print();
    //g.VectorToCSV();

    // Dijkstra's on FirstStep
    vector<Graph::Node*> nodes = g.getNodes();
    vector<Graph::Node*> test_path = g.Dijkstra(nodes[0]);
    // printing it out 
    // for (auto& node : test_path) {
    //     cout << node->name << '(' << node->time << ')' <<  " -> " << endl;;
    // }

    // write to CSV for bazookaCow
    ofstream csv_file("data/dijkstras-output.csv");
    for (auto& node : test_path ) {
        csv_file << node -> name << "," <<  "\n";
    }
    csv_file.close();
    return 0;
}