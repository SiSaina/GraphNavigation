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

#include "GraphList.h"

/*==================Insert node========================*/
void GraphList::InsertNode(int nodeLabel)
{
	// check if node already exists before inserting
	if (NodeExists(nodeLabel)) throw "Node already exist";

	// map nodeLabel to index and index to label
	nodeIndices[nodeLabel] = maxIndex;
	nodeLabels[maxIndex] = nodeLabel;

	// create a new adjacency list for the new node
	vector<pair<int, double>> newVector;

	// add the new adjacency list to the graph
	adjList.push_back(newVector);
	maxIndex++;
}

/*==================Connect========================*/
void GraphList::Connect(int nodeA, int nodeB, double weight) {
	if (!NodeExists(nodeA) || !NodeExists(nodeB)) throw "Node does not exist";

	// check if edge already exists before connecting
	if (AreConnected(nodeA, nodeB)) return;

	// get internal indices for the nodes
	int indexA = nodeIndices[nodeA];
	int indexB = nodeIndices[nodeB];

	// connect nodeA to nodeB and nodeB to nodeA
	adjList[indexA].push_back({ indexB, weight });

	// reverse connect (undirected graph)
	adjList[indexB].push_back({ indexA, weight });
}

/*==================AreConnected========================*/
bool GraphList::AreConnected(int nodeA, int nodeB) {
	if (!NodeExists(nodeA) || !NodeExists(nodeB)) throw "Node does not exist";
	
	int indexA = nodeIndices[nodeA];
	int indexB = nodeIndices[nodeB];

	// check if indexB is in the adjacency list of indexA
	for (pair<int, double> neighbour : adjList[indexA]) {
		if (neighbour.first == indexB) return true;
	}
	return false;
}

/*==================Get Neighbour List========================*/
vector<pair<int, double>> GraphList::GetNeighbourList(int node)
{
	// store internal index of the node for adjacency list access
	int index = nodeIndices[node];

	// convert internal indices back to labels for the result
	vector<pair<int, double>> result;

	// reserve space for the result
	result.reserve(adjList[index].size());

	// iterate through the adjacency list of the node and convert indices to labels
	for (const pair<int, double>& edge : adjList[index]) {
		int label = nodeLabels[edge.first]; // index -> label
		result.push_back({ label, edge.second });
	}

	return result;
}