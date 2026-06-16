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

	vector<pair<int, int>> pathAStar; // reconstructed path from start to exit
	bool isPathFound; // found: track whether a valid path has been found
	map<pair<int, int>, double> gCost; // best g-cost found for each cell

	/*
	============================================================
	Purpose:
		- Core A* function that finds the shortest path from start to end on the given map.
	Parameters:
		- map: pointer to the Map object representing the grid
		- startCell: pair of (row, col) for the starting cell
		- endCell: pair of (row, col) for the exit cell
	Returns: none
		- the result is store in path and cost attributes
	============================================================
	*/
	void AStar(Map* map, pair<int, int> startCell, pair<int, int> endCell);

	/*
	============================================================
	Purpose:
		- Returns a vector of walkable neighbouring cells for the given current cell
	Parameters:
		- map: pointer to the Map object representing the grid
		- currentCell: the current cell for which neighbours are to be found
		- goalCell: the goal cell used to calculate heuristic values
	Returns: a vector of neighbouring cells with updated g and h costs
	============================================================
	*/
	vector<Cell> GetNeighbours(Map* map, const Cell& currentCell, const Cell& goalCell);

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
		- startCell: pair of (row, col) for the starting cell
		- endCell: pair of (row, col) for the exit cell
	Returns: TRUE if a path is found, FALSE otherwise
	============================================================
	*/
	bool FindPath(Map* map, pair<int, int> startCell, pair<int, int> endCell);

	// return TRUE if a path was found, FALSE otherwise
	bool PathFound() const;

	// returns the reconstructed path from start to exit
	const vector<pair<int, int>>& GetPath() const;

	/*
	============================================================
	Purpose:
		- Helper function used in AStar
		- Reconstructs the final path after the goal has been reached
		- Starts from the goal cell and follows parent links stored
		  in the Closed List until the start cell is reached
		- Stores the resulting path in pathAStar
	Parameters:
		- startPosition: pair of (row, col) representing the start cell
		- endPosition: pair of (row, col) representing the goal cell
	============================================================
	*/
	void ReconstructPath(pair<int, int> startPosition, pair<int, int> endPosition);

	/*
	============================================================
	Purpose:
		- Helper function used in AStar
		- Processes all valid neighbouring cells of the current cell
		- Checks whether each neighbour has been visited before
		- Updates the best known g-cost if a cheaper path is found
		- Adds valid neighbours to the Open List for future exploration
	Parameters:
		- map: pointer to the Map object representing the grid
		- currentCell: the cell currently being explored
		- goalCell: the destination cell used for heuristic calculations
	============================================================
	*/
	void ProcessNeighbours(Map* map, const Cell& currentCell, const Cell& goalCell);

	/*
	============================================================
	Purpose:
		- Helper function used in AStar
		- Initializes the data structures required for A* search
		- Calculates the initial heuristic cost from the start cell to the goal cell
		- Creates the start node and inserts it into the Open List
		- Records the initial g-cost of the start cell
	Parameters:
		- startPosition: pair of (row, col) representing the start cell
		- goalCell: the destination cell used for heuristic calculations
	============================================================
	*/
	void InitializeSearch(pair<int, int> startPosition, const Cell& goalCell);

	// display the found path (mark by path cell with 'p')
	void DisplayPath(Map* map) const;

	// save found path to .txt file
	bool SavePath(Map* map, const string& filename) const;
};
