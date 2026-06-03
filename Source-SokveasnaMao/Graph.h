#pragma once
#include <vector>
#include <map>
using namespace std;

/*
============================================================
					 Graph Abstract Class
============================================================

Purpose:
Defines the interface for a graph data structure that can be used 
for pathfinding algorithms like DFS, BFS, and A*. 
This class is intended to bne inherited by specific graph 
implementations (e.g., adjacency list, adjacency matrix).

Reponsibilities:
- Store mapping between node labels and internal indices
- Provide interface for graph operations
- Support weighted graph traversal
*/
class Graph
{
protected:
	map<int, int> nodeIndices; // label -> index, 's' -> 0, 'a' -> 1, 'b' -> 2
	map<int, int> nodeLabels; // index -> label, '0' -> 's', '1' -> 'a', '2' -> 'b'
	int maxIndex = 0; // track number of nodes inserted
public:

	// virtual destructor to ensure proper cleanup of derived classes
	virtual ~Graph() = default;

	// getter methods for node mappings
	map<int, int> GetNodeIndices() const { return nodeIndices; }; // return label to index mapping
	map<int, int> GetNodeLabels() const { return nodeLabels; }; // return index to label mapping

	// pure virtual methods to be implemented by derived classes
	// add node to graph with given label (e.g., 's', 'a', 'b')
	virtual void InsertNode(int label) = 0;
	// connect two nodes with given weight (e.g., 's' to 'a' with weight 1.0)
	virtual void Connect(int nodeA, int nodeB, double weight) = 0;
	// return TRUE if nodeA and nodeB are directly connected (i.e., edge exists)
	virtual bool AreConnected(int nodeA, int nodeB) = 0;
	
	// use pair for weight graph
	virtual vector<pair<int, double>> GetNeighbourList(int node) = 0;

	// return TRUE if node exist
	bool NodeExists(int label)
	{
		// check if label exists in nodeIndices map
		return nodeIndices.find(label) != nodeIndices.end();
	}
	// return TRUE if nodeA and nodeB are directly connected (i.e., edge exists)
	int GetNumNodes()
	{
		// return the number of nodes in the graph by checking the size of nodeIndices map
		return nodeIndices.size();
	}
};

