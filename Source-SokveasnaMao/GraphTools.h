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
	Function: GetGraphFromMap
	Purpose: 
		- Converts a Map object into a GraphList representation.
		- Each node in the graph corresponds to a valid cell in the map (e.g., 's', 'a' to 'j').
		- Edges are created between nodes based on proximity (e.g., connect each node to its 2 nearest neighbors).
	Parameters:
		map: pointer to the Map object to convert
	Returns:
		- A pointer to a GraphList object representing the graph derived from the map
	============================================================
	*/
	static GraphList* GetGraphFromMap(Map* map);
	
	/*
	============================================================
	Functions: GetEuclideanDistance, GetManhattanDistance
	Purpose: 
		- Calculate the distance between two points (row1, col1) and (row2, col2) using different metrics.
		- GetEuclideanDistance: calculates the straight-line distance (L2 norm).
		- GetManhattanDistance: calculates the distance based on grid movement (L1 norm).
	Parameters:
		row1, col1: coordinates of the first point
		row2, col2: coordinates of the second point
	Returns:
		- The calculated distance as a double value
	============================================================
	*/
	static double GetEuclideanDistance(int row1, int col1, int row2, int col2);
	static double GetManhattanDistance(int row1, int col1, int row2, int col2);

	/*
	============================================================
	Function: Depth-First Search (DFS) and Depth-First Search Visit (DFSVisit)
	Purpose:
		- Perform a depth-first search on the graph starting from a given node.
		- DFSVisit is a helper function for DFS to recursively visit nodes.
	Parameters of DFS:
		graph: pointer to the GraphList object
		start: starting node for the DFS
	Parameters of DFSVisit:
		graph: pointer to the GraphList object
		node: current node being visited
		visited: set of visited nodes (used in DFSVisit), use reference to modify the original set in DFS
	Returns:
		- DFSVisit: void (print the order of visited node)
	============================================================
	*/
	static void DFS(GraphList* graph, int start);
	static void DFSVisit(GraphList* graph, int node, set<int>& visited);

	/*
	============================================================
	Function: Breadth-First Search (BFS)
	Purpose:
		- Perform a breadth-first search on the graph starting from a given node.
	Parameters:
		graph: pointer to the GraphList object
		start: starting node for the BFS
	Return:
		- BFS: void (prints the order of visited nodes)
	============================================================
	*/
	static void BFS(GraphList* graph, int start);

	/*
	============================================================
	Function: DisplayGraphList
	Purpose:
		- Display the graph in a readable format (adjacency list)
		- showing each node and its neighbors with edge weights.
		- have option bring which node first (e.g., 's' first, then 'a' to 'j')
	Parameters:
		graph: pointer to the GraphList object
	Returns:
		- Readable format
		Example: 
			s a:1.00 b:2.50
			a s:1.00 c:1.50
	============================================================
	*/
	static void DisplayGraphList(GraphList* graph);

	/*
	============================================================
	Function: PrintAllNodeDistances
	Purpose:
		- display the graph in a readable format (adjacency list)
		- showing each node and the distances to all other nodes (using Euclidean distance).
		- use for debugging and verification of the graph construction from the map
	Parameters:
		- map: pointer to the Map object (used to extract node positions for distance calculation)
	Returns:
		- Readable format
		Example:
			s a:1.00 b:2.50
			a s:1.00 c:1.50
	============================================================
	*/
	static void PrintAllNodeDistances(Map* map);
};

