#include <iostream>
#include "../src/graph.h"

using namespace std;

int main()
{

    cout << "Main function running; setting up graph" << endl;
    Graph g("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    cout << "" << endl;

    cout << "Anypercent via Dijkstra's running; outputted to data/anypercent-output.csv for input to visualization" << endl;
    vector<Graph::Node *> anypercent_route = g.Dijkstra(nodes[0], anypercent);
    g.VectorToCSV(anypercent_route, "/workspaces/cs225env/225-final-proj/data/anypercent-output.csv", anypercenttime);
    cout << "Computed time to complete Anypercent route: " << g.getAnypercentTotal() << " seconds; " << g.getAnypercentTotal() / 60.00 << " minutes; " << g.getAnypercentTotal() / 3600.00 << " hours." << endl;
    cout << "" << endl;

    cout << "All Remembrances via Dijkstra's running; outputted to data/allrem-output.csv for input to visualization" << endl;
    vector<Graph::Node *> all_remembrances_route = g.Dijkstra(nodes[0], allremembrances);
    g.VectorToCSV(all_remembrances_route, "/workspaces/cs225env/225-final-proj/data/allrem-output.csv", allremtime);
    cout << "Computed time to complete All Remembrance Bosses route: " << g.getAllRemsTotal() << " seconds; " << g.getAllRemsTotal() / 60.00 << " minutes; " << g.getAllRemsTotal() / 3600.00 << " hours." << endl;
    cout << "" << endl;

    cout << "BFS running; outputted to data/bfs-output.csv for input to visualization" << endl;
    vector<Graph::Node *> BFSroute = g.BFS(nodes[0]);
    g.VectorToCSV(BFSroute, "/workspaces/cs225env/225-final-proj/data/bfs-output.csv", bfs);
    cout << "Computed time to complete BFS route: " << g.getBFSTotal() << " seconds; " << g.getBFSTotal() / 60.00 << " minutes; " << g.getBFSTotal() / 3600.00 << " hours." << endl;
    cout << "" << endl;

    cout << "Floyd-Warshall outputs of shortest times between bosses (all pairs shortest path):" << endl;

    cout << "Shortest time between firstStep and gatefront: " << g.shortestTimeBetween("firstStep", "gatefront") << " seconds" << endl;
    cout << "Shortest time between firstStep and margit: " << g.shortestTimeBetween("firstStep", "margit") << " seconds" << endl;
    cout << "Shortest time between godrick and redWolf: " << g.shortestTimeBetween("godrick", "redWolf") << " seconds" << endl;
    cout << "Shortest time between redWolf and godrick (does not exist):  " << g.shortestTimeBetween("redWolf", "godrick") << " seconds" << endl;
    cout << "Shortest time between firstStep and malenia : " << g.shortestTimeBetween("firstStep", "malenia") << " seconds" << endl;
    cout << "Shortest time between malenia and firstStep (does not exist): " << g.shortestTimeBetween("malenia", "firstStep") << " seconds" << endl;

    // Graph::Node* valid = g.nameToNode("firstStep");
    // Graph::Node* invalid = g.nameToNode("abc");
    // cout << valid << " | " << invalid << endl;

    // Graph g("data/test_node.csv", "data/test_prereqs.csv");
    //  vector<vector<double>> test_all_paths = g.FloydWarshall();

    // for (unsigned int i = 0; i < test_all_paths.size(); i++)
    // {
    //     for (unsigned int j = 0; j < test_all_paths.at(i).size(); j++)
    //     {
    //         if (test_all_paths.at(i).at(j) != 9999)
    //         {
    //             cout << nodes[i]->name << '(' << nodes[i]->time << ')' << " -> " << endl;
    //             cout << test_all_paths.at(i).at(j) << endl;
    //         }
    //     }
    // }
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