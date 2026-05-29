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
class PathFinder
{
private:
	vector<pair<int, int>> path; // store final reconstructed path from start to exit
	bool found; // track valid path
	map<pair<int, int>, double> cost; // store the best g cost found

	// core A* function
	void AStar(Map* map, pair<int, int> start, pair<int, int> end);

	// return 8 walkable neighbours of current
	// apply wall blocking to prevent corner cutting
	vector<Cell> GetNeighbours(Map* map, const Cell& current, const Cell& goal);

	// distance helper function
	double GetEuclideanDistance(const Cell& a, const Cell& b) const;
	double GetManhattanDistance(const Cell& a, const Cell& b) const;

public:
	set<Cell> ClosedList;
	priority_queue < Cell, vector<Cell>, greater<Cell>> OpenList;

	// clear both lists and runs A* from start to end
	// return TRUE if path found
	bool FindPath(Map* map, pair<int, int> start, pair<int, int> end);

	// return TRUE if last FindPath call is success
	bool PathFound() const;

	// return the final reconstructed path
	const vector<pair<int, int>>& GetPath() const;

	// prints map with p cell marked
	void DisplayPath(Map* map) const;

	// save success path to file
	bool SavePath(Map* map, const string& filename) const;
};

