#include "../src/graph.h"
#include <limits>

Graph::Graph() {}

Graph::Graph(string nodes_file, string prereqs_file)
{
    // TODO: account for prereqs, decide on this
    ifstream prereqs(prereqs_file);

    ifstream infile(nodes_file);
    if (!infile.is_open())
    {
        cout << "error reading nodes infile!" << endl;
        return;
    }

    // First pass to populate all the nodes (needs to be done BEFORE edges)
    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string name;
        double time;
        // extract the name and time for the node
        getline(ss, name, ',');
        ss >> time;
        addNode(name, time);
    }
    infile.clear();            // reset the filestream state
    infile.seekg(0, ios::beg); // reset the file position to the beginning

    // Second pass to add edges
    while (getline(infile, line))
    {
        stringstream ss(line);
        vector<string> secondpass;

        // get all the names and times based on comma separator
        while (getline(ss, line, ','))
        {
            secondpass.push_back(line);
        }

        for (unsigned i = 0; i < secondpass.size(); i += 2)
        {
            // idx-0 will always be the name of original node
            string name = secondpass[0];
            // we only add after the first pair
            if (i > 1)
            {
                string related_name = secondpass[i];
                double time = stod(secondpass[i + 1]);
                addEdge(name, related_name, time);
            }
        }
    }
}

Graph::~Graph()
{
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        delete nodes.at(i);
    }
}

void Graph::addNode(string name, double time)
{
    Node *to_add = new Node;
    to_add->name = name;
    to_add->time = time;
    nodes.push_back(to_add);
}

void Graph::addEdge(string name1, string name2, double weight)
{
    Node *node1 = NULL;
    Node *node2 = NULL;
    for (Node *node : nodes)
    {
        if (node->name == name1)
        {
            node1 = node;
        }
        if (node->name == name2)
        {
            node2 = node;
        }
    }
    // if both nodes exist, updated the related adj. list
    if (node1 && node2)
    {
        node1->related[node2] = weight;
        node2->related[node1] = weight;
    }
}

void Graph::print()
{
    for (Node *node : nodes)
    {
        cout << node->name << ": " << node->time << "\t | Related:";
        for (auto &pair : node->related)
        {
            cout << " " << pair.first->name << ": " << pair.second;
        }
        cout << endl;
    }
}

vector<Graph::Node *> Graph::BFS(Node *start)
{
    vector<Node *> to_return;
    queue<Node *> q;
    q.push(start);
    while (!q.empty())
    {
        Node *top = q.front();
        q.pop();
        if (find(to_return.begin(), to_return.end(), top) == to_return.end())
        {
            to_return.push_back(top);
        }
        for (auto &it : top->related)
        {
            q.push(it.first);
        }
    }
    return to_return;
}

vector<Graph::Node *> Graph::Dijkstra(Node *start)
{
    vector<Node *> shortest_path;
    map<Node *, double> dist; // Keeps track of each nodes distances
    for (auto node : start->related)
    {
        dist[node.first] = node.second; // Sets all the nodes as keys
    }
    dist[start] = 0; // we set the start distance 0
    // Create a priority queue from accending order to get the smallest path
    priority_queue<pair<double, Node *>, vector<pair<double, Node *>>, greater<pair<double, Node *>>> Q;
    Q.push(make_pair(0, start)); // push the start
    std::set<Node *> visited;    // keep track of the node we visited
    // start Dijkstra
    while (!Q.empty())
    {
        auto u = Q.top().second; // pop from the queue
        Q.pop();

        if (visited.count(u) > 0)
        {
            continue;
        }

        visited.insert(u);

        for (auto v : u->related)
        {
            double alt = dist[u] + v.second;
            if (alt < dist[v.first])
            {
                dist[v.first] = alt;
                Q.push(make_pair(dist[v.first], v.first));
            }
        }
    }
    for (auto node : dist) // creates the shortest path
    {
        shortest_path.push_back(node.first);
    }
    return shortest_path;
}

vector<Graph::Node> Graph::SSSP(Node start, Node end)
{
    // dummy code just to it can compile
    vector<Node> to_return;
    to_return.push_back(start);
    to_return.push_back(end);
    return to_return;
}

vector<vector<double>> Graph::edgeListToAdjMatrix(const vector<Graph::Node *> nodes) {
    // initialize our adj matrix with 0s
    int n = nodes.size(); 
    vector<vector<double>> adjMatrix(n, vector<double>(n, 0)); 
    // iterate through each Node in the nodes vector
    for (int i = 0; i < n; i++) {
        Graph::Node* node = nodes[i];
        // iterate through the related map of the node
        for (auto it = node -> related.begin(); it != node -> related.end(); ++it) {
            Graph::Node* neighbor = it -> first;
            double weight = it -> second;
            int j = distance(nodes.begin(), find(nodes.begin(), nodes.end(), neighbor));
            adjMatrix[i][j] = weight; // add the edge weight to the adjacency matrix
        }
    }
    return adjMatrix;
}

// ? Visualization function ?
