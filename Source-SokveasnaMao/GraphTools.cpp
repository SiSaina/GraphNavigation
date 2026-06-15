/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : GraphTools.cpp

Description:
    Implements the GraphTools utility class
***************************************************************************/
#include "GraphTools.h"

/*==================GetGraphFromMap========================*/
GraphList* GraphTools::GetGraphFromMap(Map* map)
{
    GraphList* graph = new GraphList();

    vector<int> labels;
    vector<int> rows;
    vector<int> cols;

    // scan the map (20 by 20) and extract nodes
    for (int i = 0;i < MAP_SIZE;i++) {
        for (int j = 0;j < MAP_SIZE;j++) {
			// get the character at the current cell
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
        // distance list that store (distance, node index)
        vector<pair<double, int>> distanceList;

        // compute distance from node i to all other nodes
        for (int j = 0;j < n;j++) {
            if (i == j) continue;

            double d = GetEuclideanDistance(rows[i], cols[i], rows[j], cols[j]);

            // d is weight and j is index
            distanceList.push_back(make_pair(d, j));
        }

        // sort distances (smallest first) using lambda
        sort(distanceList.begin(), distanceList.end(),
            [](const pair<double, int>& a, const pair<double, int>& b) {
                return a.first < b.first;
            });

        // connect to the 2 closest nodes
        for (int k = 0; k < 2;k++) {
            int jIndex = distanceList[k].second;
            double weight = distanceList[k].first;

            // connect outer node i to k-th nearest neighbours
            graph->Connect(labels[i], labels[jIndex], weight);
        }
    }

    return graph;
}

/*==================Get Euclidean Distance========================*/
double GraphTools::GetEuclideanDistance(int row1, int col1, int row2, int col2)
{
	// formula: sqrt((row2 - row1)^2 + (col2 - col1)^2)
    return sqrt(
        (row2 - row1) * (row2 - row1) +
        (col2 - col1) * (col2 - col1)
    );
}

/*==================Get Manhattan Distance========================*/
double GraphTools::GetManhattanDistance(int row1, int col1, int row2, int col2)
{
	// formula: abs(row2 - row1) + abs(col2 - col1)
    return abs(row2 - row1) + abs(col2 - col1);
}

void GraphTools::PrintNode(GraphList* graph, int label)
{
    // check if node exists before printing
    if (!graph->NodeExists(label)) return;

    cout << static_cast<char>(label); // print node label

    // get neighbours
    vector<pair<int, double>> neighbours = graph->GetNeighbourList(label);

    // print neighbours and edge weights with format
    for (size_t i = 0; i < neighbours.size(); i++) {
        cout << " " << static_cast<char>(neighbours[i].first) << ":" << fixed << setprecision(2) << neighbours[i].second;
    }
    cout << endl;
}

/*==================Depth-First Search========================*/
void GraphTools::DFS(GraphList* graph, int start)
{
	// store visited nodes to avoid cycles
    set<int> visited;
    DFSVisit(graph, start, visited);
    cout << endl;
}

/*==================Depth-First Search Visit========================*/
void GraphTools::DFSVisit(GraphList* graph, int node, set<int>& visited)
{
    visited.insert(node); // mark node as visited
    cout << static_cast<char>(node) << " "; // print node into char

    // get node neighbours
    vector<pair<int, double>> neighbours = graph->GetNeighbourList(node);

    // visit each neighbour recursively
    for (int i = 0;i < neighbours.size();i++) {
		int next = neighbours[i].first; // get neighbour label

		// only visit if not visited to avoid cycles
        if (visited.find(next) == visited.end()) {
            DFSVisit(graph, next, visited);
        }
    }
}

/*==================Breath-First Search========================*/
void GraphTools::BFS(GraphList* graph, int start)
{
    queue<int> q; // control the order (FIFO)
	set<int> visited; // track visited nodes to avoid cycles

    q.push(start); // add start node to queue
    visited.insert(start); // mark it as visited

    // loop until no more node
    while (!q.empty()) {
        // take the front of the queue and print it
        int current = q.front();
        q.pop();
        cout << static_cast<char>(current) << " ";
        
        vector<pair<int, double>> neighbours = graph->GetNeighbourList(current);

        // add unvisited neighbours
        for (int i = 0;i < neighbours.size();i++) {
            int next = neighbours[i].first;

			// only add to queue if not visited to avoid cycles
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
    cout << endl;
}

/*==================Display Graph List========================*/
void GraphTools::DisplayGraphList(GraphList* graph)
{
    // s first, then a through j
    PrintNode(graph, 's');
    for (char c = 'a'; c <= 'j'; c++) {
        PrintNode(graph, static_cast<int>(c));
    }
}

/*==================Print All Node Distances========================*/
void GraphTools::PrintAllNodeDistances(Map* map)
{
    vector<int> label;
    vector<int> row;
    vector<int> col;

    // 1. Extract nodes again from map
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {

            char ch = map->GetCell(i, j);

            if (ch == 's' || (ch >= 'a' && ch <= 'j')) {
                label.push_back(ch);
                row.push_back(i);
                col.push_back(j);
            }
        }
    }

    int allNode = label.size();

    // 2. Print distances for each node
    for (int i = 0; i < allNode; i++) {

		cout << (char)label[i]; // print node label

		vector<pair<double, int>> distanceList; // store (distance, node index) for all other nodes

        for (int j = 0; j < allNode; j++) {

            if (i == j) continue;

            double d = GraphTools::GetEuclideanDistance(
                row[i], col[i],
                row[j], col[j]
            );

            distanceList.push_back({ d, j });
        }

        // sort by closest first
        sort(distanceList.begin(), distanceList.end(),
            [](const pair<double, int>& a, const pair<double, int>& b) {
                return a.first < b.first;
            });

        // print ALL distances
        for (pair<double, int>& printNode : distanceList) {
            cout << (char)label[printNode.second] << ":" << fixed << setprecision(2) << printNode.first << " ";
        }

        cout << endl;
    }
}