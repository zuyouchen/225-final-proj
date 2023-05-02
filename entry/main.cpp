#include <iostream>
#include "../src/graph.h"

using namespace std;

int main()
{
    /* GRAPH STRUCTURE SETUP */
    cout << "Main function running; setting up graph" << endl;
    Graph g("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    cout << "" << endl;

    /* RUNNING DIJKSTRA's FOR LEADING Qs */
    cout << "Anypercent via Dijkstra's running; outputted to output/anypercent-output.csv for input to visualization" << endl;
    vector<Graph::Node *> anypercent_route = g.Dijkstra(nodes[0], anypercent);
    g.VectorToCSV(anypercent_route, "output/anypercent-output.csv", anypercenttime);
    cout << "Computed time to complete Anypercent route: " << g.getAnypercentTotal() << " seconds; " << g.getAnypercentTotal() / 60.00 << " minutes; " << g.getAnypercentTotal() / 3600.00 << " hours." << endl;
    cout << "" << endl;

    cout << "All Remembrances via Dijkstra's running; outputted to output/allrem-output.csv for input to visualization" << endl;
    vector<Graph::Node *> all_remembrances_route = g.Dijkstra(nodes[0], allremembrances);
    g.VectorToCSV(all_remembrances_route, "output/allrem-output.csv", allremtime);
    cout << "Computed time to complete All Remembrance Bosses route: " << g.getAllRemsTotal() << " seconds; " << g.getAllRemsTotal() / 60.00 << " minutes; " << g.getAllRemsTotal() / 3600.00 << " hours." << endl;
    cout << "" << endl;

    /* RUNNING BFS */
    cout << "BFS running; outputted to output/bfs-output.csv for input to visualization" << endl;
    vector<Graph::Node *> BFSroute = g.BFS(nodes[0]);
    g.VectorToCSV(BFSroute, "output/bfs-output.csv", bfs);
    cout << "Computed time to complete BFS route: " << g.getBFSTotal() << " seconds; " << g.getBFSTotal() / 60.00 << " minutes; " << g.getBFSTotal() / 3600.00 << " hours." << endl;
    cout << "" << endl;

    /* RUNNING Floyd-Warshall Samples */
    cout << "Floyd-Warshall outputs of shortest times between bosses (all pairs shortest path):" << endl;

    cout << "Shortest time between firstStep and gatefront: " << g.shortestTimeBetween("firstStep", "gatefront") << " seconds" << endl;
    cout << "Shortest time between firstStep and margit: " << g.shortestTimeBetween("firstStep", "margit") << " seconds" << endl;
    cout << "Shortest time between godrick and redWolf: " << g.shortestTimeBetween("godrick", "redWolf") << " seconds" << endl;
    cout << "Shortest time between redWolf and godrick (does not exist):  " << g.shortestTimeBetween("redWolf", "godrick") << " seconds" << endl;
    cout << "Shortest time between firstStep and malenia : " << g.shortestTimeBetween("firstStep", "malenia") << " seconds" << endl;
    cout << "Shortest time between malenia and firstStep (does not exist): " << g.shortestTimeBetween("malenia", "firstStep") << " seconds" << endl;
}