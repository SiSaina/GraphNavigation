#pragma once
#include "GraphList.h"
#include "Map.h"
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <iomanip>
#include <iostream>

class GraphTools
{
public:
	// build graph from grid map, where certain cell become nodes
	// each node connect to its two closest neighbors using Euclidean distance
	// return graph
	static GraphList* GetGraphFromMap(Map* map);
	
	// get distance between node
	static double GetEuclideanDistance(int row1, int col1, int row2, int col2);
	static double GetManhattanDistance(int row1, int col1, int row2, int col2);

	// DFS algorithm
	// DFS depend on edge weight not insertion order
	static void DFS(GraphList* graph, int start);
	static void DFSVisit(GraphList* graph, int node, set<int>& visited);

	// BFS algorithm
	static void BFS(GraphList* graph, int start);

	static void Display(GraphList* graph);
	static void PrintAllNodeDistances(Map* map);
};

