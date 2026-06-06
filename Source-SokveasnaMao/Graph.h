/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : Graph.h

Description:
	Defines the Graph abstract class which serves as a 
	base for different graph implementations
***************************************************************************/

#pragma once
#include <vector>
#include <map>
using namespace std;

/*
============================================================
Graph Abstract Class
============================================================

Purpose:
	- Defines a generic graph interface used for pathfinding
	- algorithms such as DFS, BFS, and A*.

	- This class is designed to be inherited by concrete graph
	- implementations (e.g., adjacency list, adjacency matrix).

Description:
	- Store mapping between node labels and internal indices
	- Provide a standard interface for graph operations
	- Support weighted graph traversal
============================================================
*/
class Graph
{
protected:
	/*
	nodeIndices:
		Maps node label -> internal index
		Example: 's' -> 0, 'a' -> 1, 'b' -> 2
	*/
	map<int, int> nodeIndices;
	/*
	nodeLabels:
		Maps internal index -> node label
		Example: 0 -> 's', 1 -> 'a', 2 -> 'b'
	*/
	map<int, int> nodeLabels;

	// tracks number of nodes inserted
	int maxIndex = 0;
public:
	/*
	Purpose:
		ensures proper cleanup of resources in derived graph classes.
	*/
	virtual ~Graph() = default;

	// return node indices, label -> index
	map<int, int> GetNodeIndices() const { return nodeIndices; }
	// return node label, index -> label
	map<int, int> GetNodeLabels() const { return nodeLabels; }

	/*
	Purpose:
		- inserts a new node with the given label into the graph.
	Parameters:
		- label: the label of the node to insert
	*/
	virtual void InsertNode(int label) = 0;

	/*
	Purpose:
		- connects two nodes with a weighted edge
		- If the nodes do not exist, they should be created first
	Parameters:
		- nodeA: the label of the first node
		- nodeB: the label of the second node
		- weight: the weight of the edge connecting nodeA and nodeB
	*/
	virtual void Connect(int nodeA, int nodeB, double weight) = 0;

	/*
	Purpose:
		- checks if two nodes are directly connected by an edge
	Parameters:
		- nodeA: the label of the first node
		- nodeB: the label of the second node
	*/
	virtual bool AreConnected(int nodeA, int nodeB) = 0;
	
	/*
	Purpose:
		- retrives all neighbors and their edge weights for a given node
	Parameters:
		- node: label of the node to retrieve neighbors for
	Returns: 
		- vector of pairs containing neighbor labels(int) and edge weights(double)
	*/
	virtual vector<pair<int, double>> GetNeighbourList(int node) = 0;

	/*
	Purpose:
		- checks if a node with the given label exists in the graph
	Parameters:
		- label: node label to check (e.g., 's', 'a', 'b')
	Returns: TRUE if node exists, FALSE otherwise
	*/
	bool NodeExists(int label)
	{
		return nodeIndices.find(label) != nodeIndices.end();
	}
	
	// return the total number of nodes in the graph
	int GetNumNodes()
	{
		return nodeIndices.size();
	}
};

