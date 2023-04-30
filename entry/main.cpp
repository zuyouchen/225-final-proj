#include <iostream>
#include "../src/graph.h"

using namespace std;

int main() {
    cout << "Main function running" << endl;
    Graph g("data/nodes.csv", "data/prereqs.csv");
    g.print();
    //g.VectorToCSV();
    return 0;
}