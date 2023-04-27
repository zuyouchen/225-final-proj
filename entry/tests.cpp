#include "../src/graph.h"
#include <iostream> 
#include <cassert>
using namespace std;

void testGraphPopulation() {
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node*> nodes = g.getNodes();
    assert(nodes[0] -> name == "node1" && nodes[0] -> time == 10);
    assert(nodes[0] -> related.size() == 1);
    assert(nodes[0] -> related.count(nodes[1]) == 1);

    assert(nodes[1] -> name == "node2" && nodes[1] -> time == 15);
    assert(nodes[1] -> related.size() == 2);
    assert(nodes[1] -> related.count(nodes[0]) == 1 && nodes[1] -> related.count(nodes[2]) == 1);

    assert(nodes[2] -> name == "node3" && nodes[2] -> time == 40);
    assert(nodes[2] -> related.size() == 1);
    assert(nodes[2] -> related.count(nodes[1]) == 1);
}

void testAddNode() {
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node*> nodes = g.getNodes();
    size_t original_size = nodes.size();

    g.addNode("TestNode", 0);

    vector<Graph::Node*> new_nodes = g.getNodes();
    size_t new_size = new_nodes.size();

    assert(new_size = original_size + 1);
    assert(g.getNodes().at(g.getNodes().size() - 1)->name == "TestNode");
    assert(g.getNodes().at(g.getNodes().size() - 1)->time == 0);
    assert(g.getNodes().at(g.getNodes().size() - 1)->related.size() == 0);
}

void testAddEdge() {
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node*> nodes = g.getNodes();

    // complete nonsense edge just for testing purposes
    g.addEdge("node1", "node3", -1);

    Graph::Node* node1 = nodes.at(0);
    Graph::Node* node3 = nodes.at(nodes.size() - 1);
    map<Graph::Node*, double> node1Related = node1->related;
    map<Graph::Node*, double> node3Related = node3->related;

    assert(node1Related.count(node3) != 0);
    assert(node3Related.count(node1) != 0);
    assert(node1->related.at(node3) == -1);
    assert(node3->related.at(node1) == -1);

}

void testBFS() {
    Graph g("data/test_nodes.csv", "data/test_prereqs.csv");
    vector<Graph::Node*> nodes = g.getNodes();
    vector<Graph::Node*> bfs_result = g.BFS(nodes.at(0));
    // Test BFS visits every node
    assert(bfs_result.size() == nodes.size());

    // test on our actual graph
    Graph g2("data/nodes.csv", "data/prereqs.csv");
    vector<Graph::Node*> nodes2 = g.getNodes();

    // only ever start BFS at firstStep node
    vector<Graph::Node*> bfs_result2 = g2.BFS(nodes.at(0));

    // Test BFS visits every node
    assert(bfs_result2.size() == nodes2.size());
}

int main() {
    cout << "Test file running" << endl;
    cout << "Testing Graph Population..." << endl;
    testGraphPopulation();
    cout << "Testing Add Node..." << endl;
    testAddNode();
    cout << "Testing Add Edge..." << endl;
    testAddEdge();
    cout << "Testing BFS..." << endl;
    cout << "All tests passed" << endl;
    return 0;
}