#include <iostream>
#include "../src/graph.h"

using namespace std;

int main()
{
    cout << "Main function running" << endl;
    Graph g("data/test_node.csv", "data/test_prereqs.csv");
    // g.print();
    // g.VectorToCSV();

    // Dijkstra's on FirstStep
    vector<Graph::Node *> nodes = g.getNodes();

    // vector<Graph::Node *> test_path = g.Dijkstra(nodes[0]);

    vector<vector<double>> test_all_paths = g.FloydWarshall();

    for (unsigned int i = 0; i < test_all_paths.size(); i++)
    {
        for (unsigned int j = 0; j < test_all_paths.at(i).size(); j++)
        {
            if (test_all_paths.at(i).at(j) != 9999)
            {
                cout << nodes[i]->name << '(' << nodes[i]->time << ')' << " -> " << endl;
                cout << test_all_paths.at(i).at(j) << endl;
            }
        }
    }
    // printing it out
    // for (auto& node : test_path) {
    //     cout << node->name << '(' << node->time << ')' <<  " -> " << endl;;
    // }

    // write to CSV for bazookaCow
    // ofstream csv_file("data/dijkstras-output.csv");
    // for (auto &node : test_path)
    // {
    //     csv_file << node->name << ","
    //              << "\n";
    // }
    // csv_file.close();
    // return 0;
}