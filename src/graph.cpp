#include "../src/graph.h"
#include <limits>

#define INF 99999

Graph::Graph() {}

Graph::Graph(string nodes_file, string prereqs_file)
{

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

    ifstream prereqs(prereqs_file);
    string line2;
    while (getline(prereqs, line2))
    {
        stringstream ss2(line2);
        // string name;
        // double time;
        // // extract the name and time for the node
        // getline(ss, name, ',');
        // ss >> time;
        // addNode(name, time);
        string node;
        string prereq;
        getline(ss2, node, ',');
        ss2 >> prereq;
        prereq.pop_back();
        if (prereq == "two_shard_bearers") {
            for (size_t i = 0; i < nodes.size(); ++i) {
                if (nodes.at(i)->name == node) {
                    nodes.at(i)->shard_bearer_prereq = 2;
                }
            }
        } else {
            for (size_t i = 0; i < nodes.size(); ++i) {
                if (nodes.at(i)->name == node) {
                    for (size_t j = 0; j < nodes.size(); ++j) {
                        if (nodes.at(j)->name == prereq) {
                            nodes.at(i)->prereq = nodes.at(j);
                        }
                    }
                }
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
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes.at(i)->prereq) {
            cout << nodes.at(i)->name << ", Prereq node: " << nodes.at(i)->prereq->name << endl;
        } else if (nodes.at(i)->shard_bearer_prereq != 0) {
            cout << nodes.at(i)->name << ", Required Shard Bearers: " << nodes.at(i)->shard_bearer_prereq << endl;
        }
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

// Graph::Node* Graph::minRelative(Node* node) {
//     int min_dist = INF;
//     Node* tmp = NULL;
//     for (auto& it : node->related) {
//         if (it.second < min_dist) {
//             tmp = it.first;
//         }
//     }
//     return tmp;
// }


// CURRENT THOUGHTS ON HANDLING PATHFINDING:
// Prereqs: before popping a node, make sure its prereqs are accounted for. If not, keep in queue
// Fast travel: when arriving at a node without an exit, return to the node with the gratest number of
// unexplored edges
// Possibly fixed? -Evan 4/30
vector<Graph::Node*> Graph::Dijkstra(Node* start)
{
    map<Node*, double> dist; // dist from start -> node 
    map<Node*, Node*> prev; // prev node on shortest path 
    unordered_map<Node*, bool> seen; // whether we have visited

    for (auto node : nodes) {
        dist[node] = INF;
        prev[node] = nullptr;
        seen[node] = false;
    }

    dist[start] = 0;
    vector<Node*> path;

    priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<pair<double, Node*>>> Q;
    Q.push(make_pair(0, start));

    while (!Q.empty()) {
        Node* u = Q.top().second;
        Q.pop();
        seen[u] = true;

        if (u->name == "godrick" || u->name == "rennala" || u->name == "radahn" || u->name == "rykard") {
            shard_bearers_slain++;
        }

        // if we have not visited and a shorter path is found
        for (auto v : u->related) {
            if (!seen[v.first] && (dist[u] + v.second) < dist[v.first]) {
                // update distances and push to the Q
                dist[v.first] = dist[u] + v.second;
                prev[v.first] = u;
                Q.push(make_pair(dist[v.first], v.first));
            }
        }

        // add u to the path vector, this needed to be OUTSIDE of the updating loop
        path.push_back(u);
    }
    return path;

    // --- PREVIOUS IMPLEMENTATION (Before Evan changes 4/30/23) /// 
    // size_t size = nodes.size();
    // map<Node*, double> dist;
    // map<Node*, Node*> prev;
    // unordered_map<Node*, bool> seen;
    // for (size_t i = 0; i < size; ++i) {
    //     dist.insert({nodes.at(i), INF});
    //     prev.insert({nodes.at(i), NULL});
    //     seen.insert({nodes.at(i), false});
    // }

    // dist[start] = 0; // distance of start is 0
    // vector<Node*> path;

    // priority_queue<pair<double, Node *>, vector<pair<double, Node *>>, greater<pair<double, Node *>>> Q;
    // Q.push(make_pair(0, start));

    // while(!Q.empty()) {
    //     Node* u = Q.top().second;
    //     Q.pop();
    //     seen[u] = true;
    //     if (u->name == "godrick" || u->name == "rennala" || u->name == "radahn" || u->name == "rykard") {
    //         shard_bearers_slain++;
    //     }
    //     for(auto v : u->related) {
    //         if (seen[v.first] == false && (dist[u] + (v.second)) < dist[v.first]) {
    //             dist[v.first] = (dist[u]+(v.second));
    //             prev[v.first] = u;
    //             path.push_back(u);
    //             Q.push(make_pair(dist[v.first], v.first));
    //         }
    //     }
    // }
    // return path;


    // -------------------------- ?? -------------------------- //
    // vector<Node *> shortest_path;
    // map<Node *, double> dist; // Keeps track of each nodes distances
    // for (auto node : start->related)
    // {
    //     dist[node.first] = node.second; // Sets all the nodes as keys
    // }
    // dist[start] = 0; // we set the start distance 0
    // // Create a priority queue from accending order to get the smallest path
    // priority_queue<pair<double, Node *>, vector<pair<double, Node *>>, greater<pair<double, Node *>>> Q;
    // Q.push(make_pair(0, start)); // push the start
    // std::set<Node *> visited;    // keep track of the node we visited
    // // start Dijkstra
    // while (!Q.empty())
    // {
    //     auto u = Q.top().second; // pop from the queue
    //     Q.pop();

    //     if (visited.count(u) > 0)
    //     {
    //         continue;
    //     }

    //     visited.insert(u);

    //     for (auto v : u->related)
    //     {
    //         double alt = dist[u] + v.second;
    //         if (alt < dist[v.first])
    //         {
    //             dist[v.first] = alt;
    //             Q.push(make_pair(dist[v.first], v.first));
    //         }
    //     }
    // }
    // for (auto node : dist) // creates the shortest path
    // {
    //     shortest_path.push_back(node.first);
    // }
    // return shortest_path;
}

vector<vector<double>> Graph::FloydWarshall()
{
    vector<vector<double>> adj_matrix = edgeListToAdjMatrix(nodes);
    int n = nodes.size();
    vector<vector<double>> dist(n, vector<double>(n, INF));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                dist[i][j] = INF;
            }
            else if (adj_matrix[i][j] != 0)
            {
                dist[i][j] = adj_matrix[i][j];
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

vector<Graph::Node> Graph::SSSP(Node start, Node end)
{
    // dummy code just to it can compile
    vector<Node> to_return;
    to_return.push_back(start);
    to_return.push_back(end);
    return to_return;
}

vector<vector<double>> Graph::edgeListToAdjMatrix(const vector<Graph::Node *> nodes)
{
    // initialize our adj matrix with 0s
    int n = nodes.size();
    vector<vector<double>> adjMatrix(n, vector<double>(n, INF));
    // iterate through each Node in the nodes vector
    for (int i = 0; i < n; i++)
    {
        Graph::Node *node = nodes[i];
        // iterate through the related map of the node
        for (auto it = node->related.begin(); it != node->related.end(); ++it)
        {
            Graph::Node *neighbor = it->first;
            double weight = it->second;
            int j = distance(nodes.begin(), find(nodes.begin(), nodes.end(), neighbor));
            adjMatrix[i][j] = weight; // add the edge weight to the adjacency matrix
        }
    }
    return adjMatrix;
}

void Graph::VectorToCSV() {
    vector<Node*> v = Dijkstra(nodes.at(0));
    std::ofstream csv;
    csv.open("/workspaces/cs225env/225-final-proj/data/output.csv");
    for (size_t i = 0; i < v.size(); ++i) {
        csv << v.at(i)->name << '\n';
    }
    csv.close();
}

// ? Visualization function ?
