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

int main() {
    cout << "Test file running" << endl;
    cout << "Testing Graph Population..." << endl;
    testGraphPopulation();
    cout << "All tests passed" << endl;
    return 0;
}