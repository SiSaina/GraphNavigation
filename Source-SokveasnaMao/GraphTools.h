/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : GraphTools.h

Description:
	Provides utility functions for graph operations, DFS and BFS.
***************************************************************************/

#pragma once
#include "GraphList.h"
#include "Map.h"
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <iomanip>
#include <iostream>

/*
============================================================
Graph Tools Class
============================================================
Purpose:
	- Provides utility functions for graph operations, DFS and BFS.
Features:
	- Convert a Map into a GraphList representation
	- Calculate Euclidean and Manhattan distances
	- Perform DFS and BFS
	- Display graph structure
Used by:
	- GraphList class
	- Map class
============================================================
*/
class GraphTools
{
public:

	/*
	============================================================
	Purpose: 
		- Converts a Map object into a GraphList representation
		- Each node in the graph corresponds to a valid cell in the map (e.g., 'w', 'a' to 'j')
		- Edges are created between nodes based on proximity (e.g., connect each node to its 2 nearest neighbors)
	Parameters:
		- map: pointer to the Map object to convert
	Returns: A pointer to a GraphList object representing the graph derived from the map
	============================================================
	*/
	static GraphList* GetGraphFromMap(Map* map);
	
	// calculate Euclidean distance between two points (row1, col1) and (row2, col2)
	static double GetEuclideanDistance(int row1, int col1, int row2, int col2);
	
	// calculate Manhattan distance between two points (row1, col1) and (row2, col2)
	static double GetManhattanDistance(int row1, int col1, int row2, int col2);

	// helper function to print the given node first (s to a then j)
	static void PrintNode(GraphList* graph, int label);

	/*
	============================================================
	Purpose:
		- Perform a depth-first search on the graph starting from a given node
	Parameters of DFS:
		- graph: pointer to the GraphList object
		- start: starting node for the DFS
	============================================================
	*/
	static void DFS(GraphList* graph, int start);

	/*
	============================================================
	Purpose:
		- DFSVisit is a helper function for DFS to recursively visit node
	Parameters of DFSVisit:
		- graph: pointer to the GraphList object
		- node: current node being visited
		- visited: set of visited nodes (used in DFSVisit), use reference to modify the original set in DFS
	Returns: print the order of visited node
	============================================================
	*/
	static void DFSVisit(GraphList* graph, int node, set<int>& visited);

	/*
	============================================================
	Purpose:
		- Perform a breadth-first search on the graph starting from a given node
	Parameters:
		- graph: pointer to the GraphList object
		- start: starting node for the BFS
	Return: prints the order of visited nodes
	============================================================
	*/
	static void BFS(GraphList* graph, int start);

	// display graph in a readable format (adjacency list)
	static void DisplayGraphList(GraphList* graph);

	/*
	============================================================
	Purpose:
		- display the graph in a readable format (adjacency list)
		- showing each node and the distances to all other nodes (using Euclidean distance)
		- use for debugging and verification of the graph construction from the map
	Parameters:
		- map: pointer to the Map object (used to extract node positions for distance calculation)
	Returns: Adjacency list format
	============================================================
	*/
	static void PrintAllNodeDistances(Map* map);
};

