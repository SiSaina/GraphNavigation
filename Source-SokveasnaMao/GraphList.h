#pragma once

/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : GraphList.h

Description:
	Defines the GraphList class, which is a concrete implementation
	of the Graph abstract class using an adjacency list representation.
	This structure is efficient for sparse graphs and supports weighted
	edges, making it suitable for BFS, DFS, and A* pathfinding.
***************************************************************************/

#include "Graph.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/*
============================================================
Class: GraphList
Purpose:
	Implements a graph using an adjacency list where each
	node stores a list of connected neighbors and edge weights.
============================================================
*/
class GraphList : public Graph
{
protected:
	/*
	Adjacency List Representation:
		adjList[i] stores all connections from node i.

		Each element is:
			pair<int, double>
			- int    : neighbor node index
			- double : edge weight
	*/
	vector<vector<pair<int, double>>> adjList;
public:
	/*
	Purpose: Constructor that initializes an empty adjacency list.
	*/
	GraphList() {};

	/*
	Purpose:
		Adds a new node to the graph using the given label.
	Parameters:
		label - unique integer identifier for the node (e.g., 's', 'a', 'b')
	*/
	void InsertNode(int label) override;
	
	/*
	Purpose:
		Creates a weighted edge between two nodes.
	Parameters:
		nodeA  - label of the first node
		nodeB  - label of the second node
		weight - weight of the edge (e.g., distance or cost)
	*/
	void Connect(int nodeA, int nodeB, double weight) override;
	
	/*
	Purpose:
		Checks if two nodes have a direct edge between them.
	Parameters:
		nodeA - label of the first node
		nodeB - label of the second node
	Returns: true if edge exists, false otherwise
	*/
	bool AreConnected(int nodeA, int nodeB) override;
	
	/*
	Purpose:
		Retrieves all neighbors and their edge weights for a given node.
	Parameters:
		node - label of the node to retrieve neighbors for
	Returns: vector of pairs containing neighbor labels and edge weights
	*/
	vector<pair<int, double>> GetNeighbourList(int node) override;
};

 