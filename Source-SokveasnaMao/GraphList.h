#pragma once
#include "Graph.h"
#include <vector>
#include <algorithm>
#include <string>
class GraphList : public Graph
{
protected:
	vector<vector<pair<int, double>>> adjList; // graph adjacencies list with weight
public:
	GraphList() {};

	void InsertNode(int label) override;
	void Connect(int nodeA, int nodeB, double weight) override;
	bool AreConnected(int nodeA, int nodeB) override;
	vector<pair<int, double>> GetNeighbourList(int node) override;
};

 