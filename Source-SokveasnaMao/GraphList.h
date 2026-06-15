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

#pragma once
#include "Graph.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
============================================================
Graph List Class
============================================================

Purpose:
	- Defines a concrete graph implementation using an adjacency list.
Description:
	- Inherits from the Graph abstract class.
	- Uses a vector of vectors to store neighbors and edge weights.
	- Supports weighted edges for pathfinding algorithms.
Inherited from:
	- Graph class
============================================================
*/
class GraphList : public Graph
{
protected:
	/*
	Adjacency List Representation:
		- adjList[i] stores all connections from node i.
		Each element is:
			- pair<int, double>
			- int    : neighbor node index
			- double : edge weight
		Example:
			- adjList[0] = { {1, 2.5}, {2, 1.0} } means:
			- Node 0 is connected to Node 1 with weight 2.5
			- Node 0 is connected to Node 2 with weight 1.0
	*/
	vector<vector<pair<int, double>>> adjList;
public:
	// constructor that initializes an empty adjacency list
	GraphList() {};

	// adds a new node to the graph using the given label
	void InsertNode(int label) override;
	
	// creates a weighted edge between two nodes
	void Connect(int nodeA, int nodeB, double weight) override;
	
	// return TRUE if both node have direct edge between them, FALSE otherwise
	bool AreConnected(int nodeA, int nodeB) override;
	
	/*
	============================================================
	Purpose:
		- retrieves all neighbors and their edge weights for a given node
	Parameters:
		- node: label of the node to retrieve neighbors for
	Returns: vector of pairs containing neighbor labels and edge weights
	============================================================
	*/
	vector<pair<int, double>> GetNeighbourList(int node) override;
};

 