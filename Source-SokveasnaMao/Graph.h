#pragma once
#include <vector>
#include <map>
using namespace std;
class Graph
{
protected:
	map<int, int> nodeIndices; // label -> index
	map<int, int> nodeLabels; // index -> label
	int maxIndex = 0;
public:

	virtual ~Graph() = default;

	map<int, int> GetNodeIndices() const { return nodeIndices; };
	map<int, int> GetNodeLabels() const { return nodeLabels; };

	virtual void InsertNode(int label) = 0;
	virtual void Connect(int nodeA, int nodeB, double weight) = 0;
	virtual bool AreConnected(int nodeA, int nodeB) = 0;
	
	// use pair for weight graph
	virtual vector<pair<int, double>> GetNeighbourList(int node) = 0;

	// return TRUE if node exist
	bool NodeExists(int label)
	{
		return nodeIndices.find(label) != nodeIndices.end();
	}
	int GetNumNodes()
	{
		return nodeIndices.size();
	}
};

