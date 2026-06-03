#include "GraphList.h"

/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : GraphList.cpp

Description:
	Implements the GraphList class using an adjacency list structure.
	Supports node insertion, edge creation, adjacency checks, and
	neighbour retrieval for graph traversal algorithms.
***************************************************************************/

/*
============================================================
Function: InsertNode
Purpose:
	Adds a new node into the graph and initializes its
	adjacency list entry.

Parameters:
	label - unique integer identifier for the node

Throws:
	"Node already exist" if node already exists
============================================================
*/
void GraphList::InsertNode(int label)
{
	if (NodeExists(label)) throw "Node already exist";

	nodeIndices[label] = maxIndex;
	nodeLabels[maxIndex] = label;

	vector<pair<int, double>> newVector;
	adjList.push_back(newVector);
	maxIndex++;
}

/*
============================================================
Function: Connect
Purpose:
	Creates an undirected weighted edge between two nodes.

Parameters:
	nodeA   - first node label
	nodeB   - second node label
	weight  - weight of the edge

Throws:
	"Node does not exist" if either node is missing
============================================================
*/
void GraphList::Connect(int nodeA, int nodeB, double weight) {
	if (!NodeExists(nodeA) || !NodeExists(nodeB)) throw "Node does not exist";

	if (AreConnected(nodeA, nodeB)) return;

	int indexA = nodeIndices[nodeA];
	int indexB = nodeIndices[nodeB];

	adjList[indexA].push_back({ indexB, weight });

	// reverse connect (undirected graph)
	adjList[indexB].push_back({ indexA, weight });
}

/*
============================================================
Function: AreConnected
Purpose:
	Checks if two nodes have a direct edge between them.

Parameters:
	nodeA - first node label
	nodeB - second node label

Returns:
	true if edge exists, false otherwise

Throws:
	"Node does not exist" if either node is missing
============================================================
*/
bool GraphList::AreConnected(int nodeA, int nodeB) {
	if (!NodeExists(nodeA) || !NodeExists(nodeB)) throw "Node does not exist";
	
	int indexA = nodeIndices[nodeA];
	int indexB = nodeIndices[nodeB];

	for (pair<int, double> neighbour : adjList[indexA]) {
		if (neighbour.first == indexB) return true;
	}
	return false;
}

/*
============================================================
Function: GetNeighbourList
Purpose:
	Returns all neighbours of a node in (label, weight) format.

Parameters:
	node - node label

Returns:
	vector<pair<int,double>> of connected nodes

Notes:
	Converts internal indices back to node labels.
============================================================
*/
vector<pair<int, double>> GraphList::GetNeighbourList(int node)
{
	int index = nodeIndices[node];

	vector<pair<int, double>> result;
	result.reserve(adjList[index].size());

	for (const pair<int, double>& edge : adjList[index]) {
		int label = nodeLabels[edge.first]; // index -> label
		result.push_back({ label, edge.second });
	}

	return result;
}