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
Defines a generic graph interface used for pathfinding
algorithms such as DFS, BFS, and A*.

This class is designed to be inherited by concrete graph
implementations (e.g., adjacency list, adjacency matrix).

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

	nodeLabels:
		Maps internal index -> node label
		Example: 0 -> 's', 1 -> 'a', 2 -> 'b'

	maxIndex:
		Tracks number of nodes inserted
	*/
	map<int, int> nodeIndices;
	map<int, int> nodeLabels;
	int maxIndex = 0;
public:
	/*
	Purpose:
		Ensures proper cleanup of resources in derived graph classes.
	*/
	virtual ~Graph() = default;

	/*
	Getter Methods
		Returns internal mappings used for graph representation
	*/
	map<int, int> GetNodeIndices() const { return nodeIndices; } // label -> index
	map<int, int> GetNodeLabels() const { return nodeLabels; } // index -> label

	/*
		Purpose:
		Inserts a new node with the given label into the graph.
		Parameters:

	*/
	virtual void InsertNode(int label) = 0;
	// connect two nodes with given weight (e.g., 's' to 'a' with weight 1.0)
	virtual void Connect(int nodeA, int nodeB, double weight) = 0;
	// return TRUE if nodeA and nodeB are directly connected (i.e., edge exists)
	virtual bool AreConnected(int nodeA, int nodeB) = 0;
	
	/*
	Purpose:
		Retrieves all neighbors and their edge weights for a given node.
	Parameters:
		node - label of the node to retrieve neighbors for
	Returns: vector of pairs containing neighbor labels and edge weights
	*/
	virtual vector<pair<int, double>> GetNeighbourList(int node) = 0;

	/*
	Purpose:
		Checks if a node with the given label exists in the graph.
	Parameters:
		label - node label to check (e.g., 's', 'a', 'b')
	Returns: true if node exists, false otherwise
	*/
	bool NodeExists(int label)
	{
		return nodeIndices.find(label) != nodeIndices.end();
	}
	/*
	Purpose:
		Returns the total number of nodes in the graph.
	*/
	int GetNumNodes()
	{
		return nodeIndices.size();
	}
};

