/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : PathFinder.h

Description:
	Defines the PathFinder class that implements the A* pathfinding algorithm 
	to find a path from a start cell to an exit cell on a Map.
***************************************************************************/

#pragma once
#include "Cell.h"
#include "Map.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

/*
============================================================
PathFinder Class
============================================================
Purpose:
	- Implements the A* pathfinding algorithm to find a path from a start cell to an exit cell on a Map.
	- Maintains an open list (priority queue) of cells to explore and a closed list (set) of cells already explored.
	- Print and save the found path to a file.

Used for:
	- Finding a path from 's' to 'x' on the Map.
============================================================
*/

class PathFinder
{
private:
	/*
	Attributes:
		path:	store the final reconstructed path from start to exit
			Example: [(0, 0), (1, 1), (2, 2)] means the path goes from (0, 0) to (1, 1) to (2, 2)
		found:	track whether a valid path has been found
		cost:	store the best g cost found for each cell to avoid re-exploring worse paths
			Example: cost[{1, 1}] = 2.5 means the best g cost found so far to reach cell (1, 1) is 2.5
	*/
	vector<pair<int, int>> path;
	bool found;
	map<pair<int, int>, double> cost;

	/*
	Member functions:
		AStar:		core A* function
		GetNeighbours:	return 8 walkable neighbours of current cell
		GetEuclideanDistance:	distance helper function
		GetManhattanDistance:	distance helper function
	*/
	/*
	============================================================
	Function: AStar
	Purpose:
		Core A* function that finds the shortest path from start to end on the given map.
	Parameters:
		map: pointer to the Map object representing the grid
		start: pair of (row, col) for the starting cell
		end: pair of (row, col) for the exit cell
	Returns:
		- the result is store in path and cost attributes
	============================================================
	*/
	void AStar(Map* map, pair<int, int> start, pair<int, int> end);

	/*
	============================================================
	Function: GetNeighbours
	Purpose:
		Returns a vector of walkable neighbouring cells for the given current cell.
	Parameters:
		map: pointer to the Map object representing the grid
		current: the current cell for which neighbours are to be found
		goal: the goal cell used to calculate heuristic values
	Returns:
		- a vector of neighbouring cells with updated g and h costs
	============================================================
	*/
	vector<Cell> GetNeighbours(Map* map, const Cell& current, const Cell& goal);

	/*
	============================================================
	Function: GetEuclideanDistance and GetManhattanDistance
	Purpose:
		Helper functions to calculate distances between two cells.
	Parameters:
		a: the first cell
		b: the second cell
	Returns:
		- the Euclidean or Manhattan distance between the two cells
	============================================================
	Note: Use only in PathFinder not GraphTools because the heuristic is 
			specific to A* pathfinding on the grid map, and we want to keep 
			GraphTools more general for graph operations.
	*/
	double GetEuclideanDistance(const Cell& a, const Cell& b) const;
	double GetManhattanDistance(const Cell& a, const Cell& b) const;

public:
	
	// closed list for explored cells
	set<Cell> ClosedList;
	/*
	Purpose:
		Open list for frontier cells to explore
	Parameter:
		- Cell: the cell to be stored in the open list
		- vector<Cell>: the underlying container for the priority queue
		- greater<Cell>: the comparison function to prioritize cells with lower f cost (and g cost tie-breaker)
	*/
	priority_queue<Cell, vector<Cell>, greater<Cell>> OpenList;

	/*
	============================================================
	Function: FindPath
	Purpose:
		Finds the shortest path from start to end on the given map using the A* algorithm.
	Parameters:
		map: pointer to the Map object representing the grid
		start: pair of (row, col) for the starting cell
		end: pair of (row, col) for the exit cell
	Returns:
		- TRUE if a path is found, FALSE otherwise
	============================================================
	*/
	bool FindPath(Map* map, pair<int, int> start, pair<int, int> end);

	/*
	============================================================
	Function: PathFound
	Purpose:
		Checks if a valid path has been found
	Returns:
		- TRUE if a path has been found, FALSE otherwise
	============================================================
	*/
	bool PathFound() const;

	/*
	============================================================
	Function: GetPath
	Purpose:
		Returns the final reconstructed path from start to exit.
			Example: [(0, 0), (1, 1), (2, 2)] means the path goes from (0, 0) to (1, 1) to (2, 2)
	Returns:
		- a vector of pairs of (row, col) representing the path from start to exit
	============================================================
	*/
	const vector<pair<int, int>>& GetPath() const;

	/*
	============================================================
	Function: DisplayPath
	Purpose:
		Display the found path on the map by marking the path cells with 'p' and printing the map to the console.
	Parameters:
		map: pointer to the Map object representing the grid
	Returns:
		- Readable format of the map with the path marked, and summary information about the path (steps, cost, nodes closed)
	============================================================
	*/
	void DisplayPath(Map* map) const;

	/*
	============================================================
	Function: SavePath
	Purpose:
		Saves the found path to a file.
	Parameters:
		map: pointer to the Map object representing the grid
		filename: the name of the file to save the path to
	Returns:
		- TRUE if the path is successfully saved to the file, FALSE otherwise
	============================================================
	*/
	bool SavePath(Map* map, const string& filename) const;
};

