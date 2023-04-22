#include "../src/graph.h"

Graph::Graph() {}

Graph::Graph(string nodes_file, string prereqs_file) {
    // TODO: account for prereqs, decide on this
    ifstream prereqs(prereqs_file);

    ifstream infile(nodes_file);
    if (!infile.is_open()) {
        cout << "error reading nodes infile!" << endl;
        return;
    }

    // First pass to populate all the nodes (needs to be done BEFORE edges)
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string name;
        double time;
        // extract the name and time for the node
        getline(ss, name, ',');
        ss >> time;
        addNode(name, time);
    }
    infile.clear();  // reset the filestream state
    infile.seekg(0, ios::beg);  // reset the file position to the beginning

    // Second pass to add edges
    while (getline(infile, line)) {
        stringstream ss(line);
        vector<string> secondpass;

        // get all the names and times based on comma separator
        while (getline(ss, line, ',')) {
            secondpass.push_back(line);
        }

        for (unsigned i = 0; i < secondpass.size(); i += 2) {
            // idx-0 will always be the name of original node
            string name = secondpass[0];
            // we only add after the first pair
            if (i > 1) {
                string related_name = secondpass[i];
                double time = stod(secondpass[i+1]);
                addEdge(name, related_name, time);
            }
        }
    }
}

void Graph::addNode(string name, double time) {
    Node * to_add = new Node; 
    to_add -> name = name; 
    to_add -> time = time; 
    nodes.push_back(to_add);
}

void Graph::addEdge(string name1, string name2, double weight) {
    Node * node1 = NULL;
    Node * node2 = NULL;
    for (Node * node : nodes) {
        if (node -> name == name1) {
            node1 = node; 
        }
        if (node -> name == name2) {
            node2 = node; 
        }
    }
    // if both nodes exist, updated the related adj. list
    if (node1 && node2) {
        node1 -> related[node2] = weight; 
        node2 -> related[node1] = weight; 
    }
}

void Graph::print() {
    for (Node * node : nodes) {
        cout << node -> name << ": " << node -> time << "\t | Related:"; 
        for (auto& pair : node -> related) {
            cout << " " << pair.first -> name << ": " << pair.second;
        }
        cout << endl;
    }
}

vector<Graph::Node> Graph::Dijkstra(Node start) {
    // dummy code just to it can compile
    vector<Node> to_return;
    to_return.push_back(start);
    return to_return;
}

vector<Graph::Node> Graph::SSSP(Node start, Node end) {
    // dummy code just to it can compile
    vector<Node> to_return;
    to_return.push_back(start);
    to_return.push_back(end);
    return to_return;
}

vector<Graph::Node> Graph::BFS(Node start) {
    // dummy code just to it can compile
    vector<Node> to_return;
    to_return.push_back(start);
    return to_return;
}

// ? Visualization function ?
