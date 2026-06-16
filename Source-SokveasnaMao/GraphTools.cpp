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
    GraphList* tempGraph = new GraphList();

    vector<int> nodelabels;
    vector<int> nodeRows;
    vector<int> nodeCols;

    // scan the map (20 by 20) and extract nodes
    for (int i = 0;i < MAP_SIZE;i++) {
        for (int j = 0;j < MAP_SIZE;j++) {
			// get the character at the current cell
            char ch = map->GetCell(i, j);

            // only accept 's' and 'a' to 'j' as node
            if (ch == 's' || (ch >= 'a' && ch <= 'j')) {
                nodelabels.push_back(ch);
                nodeRows.push_back(i);
                nodeCols.push_back(j);

                tempGraph->InsertNode(ch);
            }
        }
    }

    int n = nodelabels.size();

    // connect each node to its 2 nearest neighbors
    for (int i = 0;i < n;i++) {
        // distance list that store (distance, node index)
        vector<pair<double, int>> distanceList;

        // compute distance from node i to all other nodes
        for (int j = 0;j < n;j++) {
            if (i == j) continue;

            double d = GetEuclideanDistance(nodeRows[i], nodeCols[i], nodeRows[j], nodeCols[j]);

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
            tempGraph->Connect(nodelabels[i], nodelabels[jIndex], weight);
        }
    }

    return tempGraph;
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

void GraphTools::PrintNode(GraphList* graphList, int nodeLabel)
{
    // check if node exists before printing
    if (!graphList->NodeExists(nodeLabel)) return;

    cout << static_cast<char>(nodeLabel); // print node label

    // get neighbours
    vector<pair<int, double>> neighbours = graphList->GetNeighbourList(nodeLabel);

    // print neighbours and edge weights with format
    for (size_t i = 0; i < neighbours.size(); i++) {
        cout << " " << static_cast<char>(neighbours[i].first) << ":" << fixed << setprecision(2) << neighbours[i].second;
    }
    cout << endl;
}

/*==================Depth-First Search========================*/
void GraphTools::DFS(GraphList* graphList, int startNode)
{
	// store visited nodes to avoid cycles
    set<int> visited;
    DFSVisit(graphList, startNode, visited);
    cout << endl;
}

/*==================Depth-First Search Visit========================*/
void GraphTools::DFSVisit(GraphList* graphList, int currentNode, set<int>& visited)
{
    visited.insert(currentNode); // mark node as visited
    cout << static_cast<char>(currentNode) << " "; // print node into char

    // get node neighbours
    vector<pair<int, double>> neighbours = graphList->GetNeighbourList(currentNode);

    // visit each neighbour recursively
    for (int i = 0;i < neighbours.size();i++) {
		int next = neighbours[i].first; // get neighbour label

		// only visit if not visited to avoid cycles
        if (visited.find(next) == visited.end()) {
            DFSVisit(graphList, next, visited);
        }
    }
}

/*==================Breath-First Search========================*/
void GraphTools::BFS(GraphList* graphList, int startNode)
{
    queue<int> queueNode; // control the order (FIFO)
	set<int> visited; // track visited nodes to avoid cycles

    queueNode.push(startNode); // add start node to queue
    visited.insert(startNode); // mark it as visited

    // loop until no more node
    while (!queueNode.empty()) {
        // take the front of the queue and print it
        int current = queueNode.front();
        queueNode.pop();
        cout << static_cast<char>(current) << " ";
        
        vector<pair<int, double>> neighbours = graphList->GetNeighbourList(current);

        // add unvisited neighbours
        for (int i = 0;i < neighbours.size();i++) {
            int next = neighbours[i].first;

			// only add to queue if not visited to avoid cycles
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                queueNode.push(next);
            }
        }
    }
    cout << endl;
}

/*==================Display Graph List========================*/
void GraphTools::DisplayGraphList(GraphList* graphList)
{
    // s first, then a through j
    PrintNode(graphList, 's');
    for (char c = 'a'; c <= 'j'; c++) {
        PrintNode(graphList, static_cast<int>(c));
    }
}

/*==================Print All Node Distances========================*/
void GraphTools::PrintAllNodeDistances(Map* map)
{
    vector<int> nodeLabel;
    vector<int> nodeRow;
    vector<int> nodeCol;

    // 1. Extract nodes again from map
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {

            char ch = map->GetCell(i, j);

            if (ch == 's' || (ch >= 'a' && ch <= 'j')) {
                nodeLabel.push_back(ch);
                nodeRow.push_back(i);
                nodeCol.push_back(j);
            }
        }
    }

    int allNode = nodeLabel.size();

    // 2. Print distances for each node
    for (int i = 0; i < allNode; i++) {

		cout << static_cast<char>(nodeLabel[i]); // print node label

		vector<pair<double, int>> distanceList; // store (distance, node index) for all other nodes

        for (int j = 0; j < allNode; j++) {

            if (i == j) continue;

            double d = GraphTools::GetEuclideanDistance(
                nodeRow[i], nodeCol[i],
                nodeRow[j], nodeCol[j]
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
            cout << static_cast<char>(nodeLabel[printNode.second]) << ":" << fixed << setprecision(2) << printNode.first << " ";
        }

        cout << endl;
    }
}