#include "GraphTools.h"

GraphList* GraphTools::GetGraphFromMap(Map* map)
{
    GraphList* graph = new GraphList();

    vector<int> labels;
    vector<int> rows;
    vector<int> cols;

    // scan the map and extract nodes
    for (int i = 0;i < MAP_SIZE;i++) {
        for (int j = 0;j < MAP_SIZE;j++) {
            char ch = map->GetCell(i, j);

            // only accept 's' and 'a' to 'j' as node
            if (ch == 's' || (ch >= 'a' && ch <= 'j')) {
                labels.push_back(ch);
                rows.push_back(i);
                cols.push_back(j);

                graph->InsertNode(ch);
            }
        }
    }

    int n = labels.size();

    // connect each node to its 2 nearest neighbors
    for (int i = 0;i < n;i++) {
        // distance list that store (distance, node_index)
        vector<pair<double, int>> distList;

        // compute distance from node i to all other nodes
        for (int j = 0;j < n;j++) {
            if (i == j) continue;

            double d = GetEuclideanDistance(rows[i], cols[i], rows[j], cols[j]);

            distList.push_back(make_pair(d, j));
        }

        // sort distances (smallest first) using lambda
        sort(distList.begin(), distList.end(),
            [](const pair<double, int>& a,
               const pair<double, int>& b) {
                return a.first < b.first;
            });

        // connect to the 2 closest nodes
        for (int k = 0; k < 2;k++) {
            int jIndex = distList[k].second;
            double weight = distList[k].first;

            // connect outer node i to its k-th nearest neighbours
            graph->Connect(labels[i], labels[jIndex], weight);
        }
    }

    return graph;
}

double GraphTools::GetEuclideanDistance(int row1, int col1, int row2, int col2)
{
    return sqrt(
        (row2 - row1) * (row2 - row1) +
        (col2 - col1) * (col2 - col1)
    );
}

double GraphTools::GetManhattanDistance(int row1, int col1, int row2, int col2)
{
    return abs(row2 - row1) + abs(col2 - col1);
}

void GraphTools::DFS(GraphList* graph, int start)
{
    set<int> visited;
    DFSVisit(graph, start, visited);
    cout << endl;
}

// depth-first traversal with greedy local ordering (by distance)
// best for exploring graphs, visual traversal and heuristic based search
// not best for shortest paths or optimal routing
void GraphTools::DFSVisit(GraphList* graph, int node, set<int>& visited)
{
    // mark node as visited
    visited.insert(node);

    // print node
    cout << static_cast<char>(node) << " ";

    // get neighbours
    vector<pair<int, double>> neighbours = graph->GetNeighbourList(node);

    // sort neighbours by edge weight
    sort(neighbours.begin(), neighbours.end(),
        [](const pair<int, double>& a,
           const pair<int, double>& b) {
                return a.second < b.second;
        });

    // visit each neighbour recursively
    for (int i = 0;i < neighbours.size();i++) {
		int next = neighbours[i].first; // get neighbour label

        if (visited.find(next) == visited.end()) {
            DFSVisit(graph, next, visited);
        }
    }
}

void GraphTools::BFS(GraphList* graph, int start)
{
    // set up
    queue<int> q; // control the order (FIFO)
    set<int> visited;

    q.push(start); // add start node to queue
    visited.insert(start); // mark it as visited

    // loop until no more node
    while (!q.empty()) {
        // take the front of the queue and print it
        int current = q.front();
        q.pop();
        cout << (char)current << " ";
        
        // get neighbours
        vector<pair<int, double>> neighbours = graph->GetNeighbourList(current);

        // add unvisited neighbours
        for (int i = 0;i < neighbours.size();i++) {
            int next = neighbours[i].first;

            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
    cout << endl;
}

void GraphTools::Display(GraphList* graph)
{
    auto printNode = [&](int label) {
        if (!graph->NodeExists(label)) return;

        cout << static_cast<char>(label);

        vector<pair<int, double>> neighbours = graph->GetNeighbourList(label);
        for (size_t i = 0; i < neighbours.size(); i++) {
            cout << " " << static_cast<char>(neighbours[i].first)
                << ":" << fixed << setprecision(2) << neighbours[i].second;
        }
        cout << endl;
        };

    // s first, then a through j
    printNode('s');
    for (char c = 'a'; c <= 'j'; c++) {
        printNode(static_cast<int>(c));
    }
}

void GraphTools::PrintAllNodeDistances(Map* map)
{
    vector<int> labels;
    vector<int> rows;
    vector<int> cols;

    // 1. Extract nodes again from map
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {

            char ch = map->GetCell(i, j);

            if (ch == 's' || (ch >= 'a' && ch <= 'j')) {
                labels.push_back(ch);
                rows.push_back(i);
                cols.push_back(j);
            }
        }
    }

    int n = labels.size();

    // 2. Print distances for each node
    for (int i = 0; i < n; i++) {

        cout << (char)labels[i];

        vector<pair<double, int>> distList;

        for (int j = 0; j < n; j++) {

            if (i == j) continue;

            double d = GraphTools::GetEuclideanDistance(
                rows[i], cols[i],
                rows[j], cols[j]
            );

            distList.push_back({ d, j });
        }

        // sort by closest first
        sort(distList.begin(), distList.end(),
            [](const pair<double, int>& a,
                const pair<double, int>& b)
            {
                return a.first < b.first;
            });

        // print ALL distances
        for (auto& p : distList) {
            cout << (char)labels[p.second]
                << ":" << fixed << setprecision(2) << p.first << " ";
        }

        cout << endl;
    }
}