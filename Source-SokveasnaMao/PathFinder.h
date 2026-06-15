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

	vector<pair<int, int>> path; // reconstructed path from start to exit
	bool found; // 	found: track whether a valid path has been found
	map<pair<int, int>, double> cost; // best g-cost found for each cell

	/*
	============================================================
	Purpose:
		- Core A* function that finds the shortest path from start to end on the given map.
	Parameters:
		- map: pointer to the Map object representing the grid
		- start: pair of (row, col) for the starting cell
		- end: pair of (row, col) for the exit cell
	Returns: none
		- the result is store in path and cost attributes
	============================================================
	*/
	void AStar(Map* map, pair<int, int> start, pair<int, int> end);

	/*
	============================================================
	Purpose:
		- Returns a vector of walkable neighbouring cells for the given current cell
	Parameters:
		- map: pointer to the Map object representing the grid
		- current: the current cell for which neighbours are to be found
		- goal: the goal cell used to calculate heuristic values
	Returns: a vector of neighbouring cells with updated g and h costs
	============================================================
	*/
	vector<Cell> GetNeighbours(Map* map, const Cell& current, const Cell& goal);

	/*
	- calculate Euclidean distance between two points (row1, col1) and (row2, col2)
	Note: Use only in PathFinder not GraphTools because the heuristic is 
			specific to A* pathfinding on the grid map
	*/
	double GetEuclideanDistance(const Cell& a, const Cell& b) const;
	/*
	- calculate Manhattan distance between two points (row1, col1) and (row2, col2)
	Note: Use only in PathFinder not GraphTools because the heuristic is
			specific to A* pathfinding on the grid map
	*/
	double GetManhattanDistance(const Cell& a, const Cell& b) const;

public:
	
	set<Cell> ClosedList; // explored cells

	/*
	============================================================
	Purpose:
		- Open list for frontier cells to explore
	Parameter:
		- Cell: the cell to be stored in the open list
		- vector<Cell>: container for the priority queue
		- greater<Cell>: comparison function to prioritize cells with lower f cost (and g cost tie-breaker)
	============================================================
	*/
	priority_queue<Cell, vector<Cell>, greater<Cell>> OpenList;

	/*
	============================================================
	Purpose:
		- Finds the shortest path from start to end on the given map using the A* algorithm.
	Parameters:
		- map: pointer to the Map object representing the grid
		- start: pair of (row, col) for the starting cell
		- end: pair of (row, col) for the exit cell
	Returns: TRUE if a path is found, FALSE otherwise
	============================================================
	*/
	bool FindPath(Map* map, pair<int, int> start, pair<int, int> end);

	// return TRUE if a path was successfully found
	bool PathFound() const;

	// returns the reconstructed path from start to exit
	const vector<pair<int, int>>& GetPath() const;

	// display the found path (mark by path cell with 'p')
	void DisplayPath(Map* map) const;

	// save found path to .txt file
	bool SavePath(Map* map, const string& filename) const;
};
