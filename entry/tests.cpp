#include "../src/graph.h"
#include <iostream>
#include <cassert>
#include <limits>
using namespace std;
#define INF 99999

void testGraphPopulation()
{
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    assert(nodes[0]->name == "node1" && nodes[0]->time == 10);
    assert(nodes[0]->related.size() == 1);
    assert(nodes[0]->related.count(nodes[1]) == 1);

    assert(nodes[1]->name == "node2" && nodes[1]->time == 15);
    assert(nodes[1]->related.size() == 2);
    assert(nodes[1]->related.count(nodes[0]) == 1 && nodes[1]->related.count(nodes[2]) == 1);

    assert(nodes[2]->name == "node3" && nodes[2]->time == 40);
    assert(nodes[2]->related.size() == 1);
    assert(nodes[2]->related.count(nodes[1]) == 1);
}

void testPrereqReading()
{
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();

    int num_prereqs = 0;
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->prereq)
        {
            num_prereqs++;
        }
    }
    int rows = 0;
    ifstream file("data/test_prereqs.csv");
    string line;
    while (getline(file, line))
    {
        rows++;
    }
    assert(num_prereqs == rows);
}

void testAddNode()
{
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    size_t original_size = nodes.size();

    g.addNode("TestNode", 0);

    vector<Graph::Node *> new_nodes = g.getNodes();
    size_t new_size = new_nodes.size();

    assert(new_size = original_size + 1);
    assert(g.getNodes()[g.getNodes().size() - 1]->name == "TestNode");
    assert(g.getNodes()[(g.getNodes().size() - 1)]->time == 0);
    assert(g.getNodes()[(g.getNodes().size() - 1)]->related.size() == 0);
}

void testAddEdge()
{
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();

    // complete nonsense edge just for testing purposes
    g.addEdge("node1", "node3", -1);

    Graph::Node *node1 = nodes[0];
    Graph::Node *node3 = nodes[nodes.size() - 1];
    map<Graph::Node *, double> node1Related = node1->related;
    map<Graph::Node *, double> node3Related = node3->related;

    assert(node1Related.count(node3) != 0);
    assert(node3Related.count(node1) != 0);
    assert(node1->related[node3] == -1);
    assert(node3->related[node1] == -1);
}

void testBFS()
{
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    vector<Graph::Node *> bfs_result = g.BFS(nodes[0]);
    // Test BFS visits every node
    assert(bfs_result.size() == nodes.size());

    // test on our actual graph
    Graph g2("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes2 = g2.getNodes();

    // only ever start BFS at firstStep node
    vector<Graph::Node *> bfs_result2 = g2.BFS(nodes2[0]);

    // Output
    g2.VectorToCSV(bfs_result2, "output/bfs-output.csv", bfs);

    // Test BFS visits every node
    assert(bfs_result2.size() == nodes2.size());
}

void testDijkstra()
{

    Graph g2("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes2 = g2.getNodes();
    vector<Graph::Node *> dijkstra_result = g2.Dijkstra(nodes2[0], allremembrances);

    // write to file for testing
    g2.VectorToCSV(dijkstra_result, "output/allrem-output.csv", allremtime);

    // make sure we hit every node
    assert(dijkstra_result.size() == nodes2.size());
}

void testAnypercent()
{
    Graph g("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    vector<Graph::Node *> dijkstra_result = g.Dijkstra(nodes[0], anypercent);
    g.VectorToCSV(dijkstra_result, "output/anypercent-output.csv", anypercenttime);

    int shard_bearers_visited = 0;
    for (size_t i = 0; i < dijkstra_result.size(); ++i)
    {
        if (dijkstra_result[i]->name == "godrick" || dijkstra_result[i]->name == "rennala" || dijkstra_result[i]->name == "radahn" || dijkstra_result[i]->name == "rykard")
        {
            shard_bearers_visited++;
        }
    }
    // for optimal speed, only kill the minimum 2 shardbearers
    assert(shard_bearers_visited == 2);
    // must still visit the final boss node
    assert(dijkstra_result[dijkstra_result.size() - 1]->name == "radagonAndEldenBeast");

}

void testFloydWarshall()
{
    Graph g("data/nodes.csv", "data/prereqs.csv");
    assert(g.shortestTimeBetween("firstStep", "gatefront") == 80);
    assert(g.shortestTimeBetween("firstStep", "margit") == 150);
    assert(g.shortestTimeBetween("godrick", "redWolf") == 249);
    assert(g.shortestTimeBetween("redWolf", "godrick") == -1);
    assert(g.shortestTimeBetween("firstStep", "malenia") == 1701);
    assert(g.shortestTimeBetween("malenia", "firstStep") == -1);
}

void testAdjListToAdjMatrix()
{
    /*
     * With our simple graph (test_nodes.csv), we should get adj matrix that looks like:
     * [[0, 20, 0],
     *  [0, 0, 25],
     *  [0, 0, 0]]
     *
     * We have asserted this but you can also uncomment the printing loops to see.
     */
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    vector<vector<double>> adjMatrix = g.adjListToAdjMatrix(nodes);
    assert(adjMatrix.size() == 3);
    assert(adjMatrix[0].size() == 3);
    // Diagonal should be INF
    assert(adjMatrix[0][0] == INF);
    assert(adjMatrix[1][1] == INF);
    assert(adjMatrix[2][2] == INF);

    // Existing edges
    assert(adjMatrix[0][1] == adjMatrix[1][0] && adjMatrix[0][1] == 20);
    assert(adjMatrix[1][2] == adjMatrix[2][1] && adjMatrix[1][2] == 25);

    // Non-existing edges (should be INF)
    assert(adjMatrix[0][2] == INF);
    assert(adjMatrix[2][0] == INF);

}

void testNameToNode()
{
    Graph g("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    // Valid Nodes
    assert(g.nameToNode("firstStep") == nodes.at(0));
    assert(g.nameToNode("gatefront") == nodes.at(1));
    // Invalid Nodes
    assert(g.nameToNode("abc") == NULL);
    assert(g.nameToNode("firststep") == NULL);
}

void testShortestTimeBetween()
{
    Graph g("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    // Nodes that are a single edge apart
    assert(g.shortestTimeBetween("firstStep", "gatefront") == 80);
    assert(g.shortestTimeBetween("lorettaHaligtree", "malenia") == 240);

    // Nodes that are >1 edge apart
    assert(g.shortestTimeBetween("firstStep", "margit") == 150);
    assert(g.shortestTimeBetween("godrick", "redWolf") == 249);

    // No valid path (invalid name)
    assert(g.shortestTimeBetween("firstStep", "abc") == -1);
    // No valid path (no path)
    assert(g.shortestTimeBetween("firstStep", "mohg") == -1);
}

int main()
{
    cout << "Test file running" << endl;

    cout << "Testing Graph Population..." << endl;
    testGraphPopulation();

    cout << "Testing Prereq Population..." << endl;
    testPrereqReading();

    cout << "Testing Add Node..." << endl;
    testAddNode();

    cout << "Testing Add Edge..." << endl;
    testAddEdge();

    cout << "Testing BFS..." << endl;
    testBFS();

    cout << "Testing All-Remembrances Dijkstra's..." << endl;
    testDijkstra();

    cout << "Testing Anypercent Dijkstra's..." << endl;
    testAnypercent();

    cout << "Testing Floyd-Warshall..." << endl;
    testFloydWarshall();

    cout << "Testing Adj List -> Adj Matrix..." << endl;
    testAdjListToAdjMatrix();

    cout << "Testing nameToNode..." << endl;
    testNameToNode();

    cout << "Testing shortestTimeBetween..." << endl;
    testShortestTimeBetween();

    cout << "All tests passed" << endl;

    return 0;
}
