#include "../src/graph.h"

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

    // Now read in prerequisite file
    ifstream prereqs(prereqs_file);
    string line2;
    while (getline(prereqs, line2))
    {
        stringstream ss2(line2);
        string node;
        string prereq;
        getline(ss2, node, ',');
        ss2 >> prereq;
        prereq.pop_back();
        if (prereq == "two_shard_bearers")
        {
            for (size_t i = 0; i < nodes.size(); ++i)
            {
                if (nodes[i]->name == node)
                {
                    nodes[i]->shard_bearer_prereq = 2;
                }
            }
        }
        else
        {
            for (size_t i = 0; i < nodes.size(); ++i)
            {
                if (nodes[i]->name == node)
                {
                    for (size_t j = 0; j < nodes.size(); ++j)
                    {
                        if (nodes[j]->name == prereq)
                        {
                            nodes[i]->prereq = nodes[j];
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
        delete nodes[i];
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
    // print relations
    for (Node *node : nodes)
    {
        cout << node->name << ": " << node->time << "\t | Related:";
        for (auto &pair : node->related)
        {
            cout << " " << pair.first->name << ": " << pair.second;
        }
        cout << endl;
    }
    // print prereqs
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->prereq)
        {
            cout << nodes[i]->name << ", Prereq node: " << nodes[i]->prereq->name << endl;
        }
        else if (nodes[i]->shard_bearer_prereq != 0)
        {
            cout << nodes[i]->name << ", Required Shard Bearers: " << nodes[i]->shard_bearer_prereq << endl;
        }
    }
}

vector<Graph::Node *> Graph::BFS(Node *start)
{
    vector<Node *> to_return;
    queue<Node *> q;
    unordered_map<Node *, bool> visited;
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        visited.insert({nodes[i], false});
    }
    visited.insert({NULL, true}); // if a node has NULL as a prereq, it can validly move to it
    q.push(start);
    while (!q.empty())
    {
        Node *top = q.front();
        while (visited[top->prereq] == false || shard_bearers_slain < top->shard_bearer_prereq)
        {
            // if we haven't gotten prereqs, re-add the node to the back of the queue for later processing
            q.push(top);
            // remove the node
            q.pop();
            // process the node after it
            top = q.front();
            // repeat until we found a node we can traverse to
        }
        q.pop();
        if (visited[top] == false)
        {
            to_return.push_back(top);
            visited[top] = true;
            BFS_total_time += top->time; // add our current node's time
            if (top->name == "godrick" || top->name == "rennala" || top->name == "radahn" || top->name == "rykard")
            {
                shard_bearers_slain++;
            }
        }
        for (auto &it : top->related)
        {
            if (visited[it.first] == false)
            {
                q.push(it.first);
                BFS_total_time += it.second; // add the distance to each other node to the time
            }
        }
    }
    return to_return;
}

// Path finding algorithm for an All-Bosses (all nodes) route or any% route, accounting for node order via prereqs;
// automatically handles fast travel due to breadth-first nature.
// Also takes in a route which determines if we run anypercent or all remembrances
vector<Graph::Node *> Graph::Dijkstra(Node *start, route r)
{
    map<Node *, double> dist; // dist from start -> node
    for (size_t i = 1; i < nodes.size(); ++i)
    {
        dist.insert({nodes[i], INF});
    }
    map<Node *, Node *> prev;            // prev node on shortest path
    unordered_map<Node *, bool> visited; // whether we have visited
    visited.insert({NULL, true});        // if a node has NULL as a prereq, it can validly move to it

    for (auto node : nodes)
    {
        dist[node] = INF;
        prev[node] = nullptr;
        visited[node] = false;
    }

    dist[start] = 0;
    vector<Node *> path;

    // Creates a priority queue of pairs of doubles (times) amd Node pointers
    // the "greater" part initiailizes the priority queue to be a minimum heap
    priority_queue<pair<double, Node *>, vector<pair<double, Node *>>, greater<pair<double, Node *>>> Q;
    Q.push(make_pair(0, start));

    while (!Q.empty())
    {
        Node *u = Q.top().second;
        // check if we're doing any anypercent, and if so, we want to remove nodes that we don't need to visit
        // determined by the helper
        if (r == anypercent)
        {
            while (shouldSkipInAnypercent(u))
            {
                Q.pop();
                u = Q.top().second;
            }
        }
        // handle prereqs
        vector<pair<double, Node *>> unvisitable_nodes;
        while (visited[u->prereq] == false || shard_bearers_slain < u->shard_bearer_prereq)
        {
            // if we haven't gotten prereqs, remove the node; it'll be added later
            unvisitable_nodes.push_back(Q.top());
            Q.pop();
            // process the node after it
            u = Q.top().second;
            // repeat until we found a node we can traverse to
        }
        Q.pop();
        visited[u] = true;

        // re add the unvisitable nodes, hoping they can be processed next time
        for (size_t i = 0; i < unvisitable_nodes.size(); ++i)
        {
            Q.push(unvisitable_nodes[i]);
        }

        // of the seven total shard_bearers, only 4 are accessible before godfrey (golden shade), so must do 2 of them
        if (u->name == "godrick" || u->name == "rennala" || u->name == "radahn" || u->name == "rykard")
        {
            shard_bearers_slain++;
        }

        // if we have not visited and a shorter path is found
        for (auto v : u->related)
        {
            if (!visited[v.first] && (dist[u] + v.second) < dist[v.first])
            {
                // once again, only add a node if we should visit it
                if ((r == anypercent && !shouldSkipInAnypercent(v.first)) || r == allremembrances)
                {
                    dist[v.first] = dist[u] + v.second;
                    prev[v.first] = u;
                    Q.push(make_pair(dist[v.first], v.first));
                }
            }
        }

        // add u to the path vector, this needed to be OUTSIDE of the updating loop
        if (count(path.begin(), path.end(), u) == 0)
        {
            if (r == anypercent)
            {
                if (!shouldSkipInAnypercent(u))
                {
                    path.push_back(u);
                }
            }
            else
            {
                path.push_back(u);
            }
        }
    }
    // hardcoded stop at Elden Beast (which is the node at index 48)
    // World record all remembrances: about 2 hours
    // World record any%: about 1 hour
    // Computes time via a helper
    if (r == allremembrances)
    {
        all_rem_total_time = computeTimeViaPath(path);
    }
    else if (r == anypercent)
    {
        anypercent_total_time = computeTimeViaPath(path);
    }
    return path;
}

double Graph::computeTimeViaPath(vector<Node *> path)
{
    double to_return = 0;
    // we want to loop through all the nodes in our path
    for (size_t i = 0; i < path.size(); ++i)
    {   
        // get the current node and its index (via another helper)
        Node *curr = path.at(i);
        size_t index = getNodeIdx(curr);
        // add the time of the current node
        to_return += nodes.at(index)->time;
        if (i > 0)
        {
            for (size_t k = index; k > 0; --k)
            {   
                // find the most recent node that would have a path to our current node and add its time
                if (nodes.at(k)->related[curr] != 0)
                {
                    to_return += nodes.at(k)->related[curr];
                }
            }
        }
    }
    return to_return;
}

bool Graph::shouldSkipInAnypercent(Node *node)
{
    // skip all optional areas, must be hardcoded to prevent the algorithm from visitng them
    if (node->name == "ancestralWoods" || node->name == "liurniaTower" || node->name == "snowfieldInner"
    || node->name == "niallMedalion" || node->name == "placidusax" || node->name == "albinauricMedalion"
    || node->name == "cariaGate" || node->name == "fiasChamps")
    {
        return true;
    }
    // if already have killed 2 demigods, don't hunt for any more
    if (shard_bearers_slain >= 2)
    {
        if (node->name == "margit" || node->name == "smarag" || node->name == "cuckooChurch"
        || node->name == "gurranq" || node->name == "radahn" || node->name == "redWolf"
        || node->name == "radahn" || node->name == "rykard" || node->name == "abductorDuo"
        || node->name == "godskinNoble")
        {
            return true;
        }
    }
    return false;
}

vector<vector<double>> Graph::FloydWarshall()
{
    vector<vector<double>> adj_matrix = adjListToAdjMatrix(nodes); // convert the adj list to a adj matrix 
    int n = nodes.size();
    vector<vector<double>> dist(n, vector<double>(n, INF));
    vector<vector<bool>> visited(n, vector<bool>(n, false)); // to avoid mirrored paths 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) // if we compare the same nodes, seting the distance = 0 and making sure we don't mirror paths.
            {
                dist[i][j] = 0;
                visited[i][j] = true;
            }
            // Igorning all infinite, visited, and 0s to avoid self loops for distances matri
            else if (adj_matrix[i][j] != INF && adj_matrix[i][j] != 0 && !visited[i][j])
            {
                dist[i][j] = adj_matrix[i][j];
                visited[i][j] = true;
                visited[j][i] = true;
            }
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                //avoiding all self loop & updating the distance if vertex k is on the shortest path from i to j.
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[i][k] != INF && dist[k][j] != INF) && (dist[i][k] != 0 && dist[k][j] != 0))
                
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    return dist; // return all distances
}

Graph::Node *Graph::nameToNode(string nodeName)
{
    // if we do find a matching node
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        if (nodes.at(i)->name == nodeName)
        {
            return nodes.at(i);
        }
    }
    // if we never find a matching node
    return NULL;
}

size_t Graph::getNodeIdx(Node *node)
{
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        if (nodes.at(i) == node)
        {
            return i;
        }
    }
    // should never reach this (because we pass a valid pointer), but need for compiler
    return 0;
}

double Graph::shortestTimeBetween(string nodeAname, string nodeBname)
{
    Node *nodeANode = nameToNode(nodeAname);
    Node *nodeBNode = nameToNode(nodeBname);
    // if either of our names are not found in the Graph
    if (nodeANode == NULL || nodeBNode == NULL)
    {
        return -1;
    }
    // convert our node pointers to their index
    size_t nodeAIdx = getNodeIdx(nodeANode);
    size_t nodeBIdx = getNodeIdx(nodeBNode);

    vector<vector<double>> shortestPathDists = FloydWarshall();
    double time = shortestPathDists[nodeAIdx][nodeBIdx];

    if (time == INF)
    {
        return -1;
    }

    return time;
}

vector<vector<double>> Graph::adjListToAdjMatrix(const vector<Graph::Node *> nodes)
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

void Graph::VectorToCSV(vector<Node *> input, string output, time_returned type)
{
    std::ofstream csv;
    csv.open(output);
    // puts "runname$seconds$minutes$hours" onto the first line for easy input into visualization
    if (type == bfs)
    {
        csv << "BFS" << '$' << BFS_total_time << '$' << BFS_total_time / 60.00 << '$' << BFS_total_time / 3600.00 << ',' << endl;
    }
    else if (type == allremtime)
    {
        csv << "All-Remembrances" << '$' << all_rem_total_time << '$' << all_rem_total_time / 60.00 << '$' << all_rem_total_time / 3600.00 << ',' << endl;
    }
    else if (type == anypercenttime)
    {
        csv << "Anypercent" << '$' << anypercent_total_time << '$' << anypercent_total_time / 60.00 << '$' << anypercent_total_time / 3600.00 << ',' << endl;
    }
    else
    {
        cout << "Invalid type input" << endl;
        csv << "INVALID TYPE" << endl;
        return;
    }
    for (size_t i = 0; i < input.size(); ++i)
    {
        csv << input[i]->name << "," << '\n';
    }
    csv.close();
}
