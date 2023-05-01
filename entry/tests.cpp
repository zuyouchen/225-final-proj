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
        if (nodes.at(i)->prereq)
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
    assert(g.getNodes().at(g.getNodes().size() - 1)->name == "TestNode");
    assert(g.getNodes().at(g.getNodes().size() - 1)->time == 0);
    assert(g.getNodes().at(g.getNodes().size() - 1)->related.size() == 0);
}

void testAddEdge()
{
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();

    // complete nonsense edge just for testing purposes
    g.addEdge("node1", "node3", -1);

    Graph::Node *node1 = nodes.at(0);
    Graph::Node *node3 = nodes.at(nodes.size() - 1);
    map<Graph::Node *, double> node1Related = node1->related;
    map<Graph::Node *, double> node3Related = node3->related;

    assert(node1Related.count(node3) != 0);
    assert(node3Related.count(node1) != 0);
    assert(node1->related.at(node3) == -1);
    assert(node3->related.at(node1) == -1);
}

void testBFS()
{
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node *> nodes = g.getNodes();
    vector<Graph::Node *> bfs_result = g.BFS(nodes.at(0));
    // Test BFS visits every node
    assert(bfs_result.size() == nodes.size());

    // test on our actual graph
    Graph g2("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes2 = g2.getNodes();

    // only ever start BFS at firstStep node
    vector<Graph::Node *> bfs_result2 = g2.BFS(nodes2.at(0));

    // Output
    g.VectorToCSV(bfs_result2, "/workspaces/cs225env/225-final-proj/data/bfs-output.csv");

    // Test BFS visits every node
    assert(bfs_result2.size() == nodes2.size());

}

void testDijkstra()
{

    Graph g;
    vector<Graph::Node *> answer;

    Graph::Node *a = new Graph::Node;
    a->name = "A";
    a->time = 0;
    Graph::Node *b = new Graph::Node;
    b->name = "B";
    b->time = numeric_limits<double>::infinity();
    Graph::Node *c = new Graph::Node;
    c->name = "C";
    c->time = numeric_limits<double>::infinity();
    answer.push_back(a);
    answer.push_back(b);
    answer.push_back(c);
    g.addNode("A", 0);
    g.addNode("B", numeric_limits<double>::infinity());
    g.addNode("C", numeric_limits<double>::infinity());

    vector<Graph::Node *> result = g.Dijkstra(a);
    for (unsigned int i = 0; i < result.size(); i++)
    {
        assert(result[i]->name == answer[i]->name && result[i]->time == answer[i]->time && result[i]->related == answer[i]->related);
    }
    Graph g2("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node *> nodes2 = g2.getNodes();
    vector<Graph::Node*> dijkstra_result = g2.Dijkstra(nodes2.at(0));
    g.VectorToCSV(dijkstra_result, "/workspaces/cs225env/225-final-proj/data/dijkstras-output.csv");
}

void testDijkstraRealGraph()
{
    /*
     * @todo
     */
}

void testFloydWarshallEasy()
{
}

void testEdgeListToAdjMatrix()
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
    vector<vector<double>> adjMatrix = g.edgeListToAdjMatrix(nodes);
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

    // --- PRINTING OUT THE ADJ MATRIX
    // for (unsigned i = 0; i < adjMatrix.size(); ++i) {
    //     for (unsigned j = 0; j < adjMatrix[i].size(); ++j) {
    //         cout << "[" << adjMatrix[i][j] << "]";
    //     }
    //     cout << endl;
    // }
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

    cout << "Testing Dijkstra..." << endl;
    testDijkstra();

    // TEST FLOYD-WARSHALL

    cout << "Testing Edge List ->  Adj Matrix..." << endl;
    testEdgeListToAdjMatrix();

    cout << "All tests passed" << endl;

    return 0;
}