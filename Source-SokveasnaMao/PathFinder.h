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
	vector<pair<int, int>> path; // reconstructed path from start to exit
	bool found;

	// core A* function
	void AStar(Map* map, pair<int, int> start, pair<int, int> end);

	// return 8 walkable neighbours of current
	// apply wall blocking to prevent corner cutting
	vector<Cell> GetNeighbours(Map* map, const Cell& current, const Cell& goal);

	double GetEuclideanDistance(const Cell& a, const Cell& b) const;
	double GetManhattanDistance(const Cell& a, const Cell& b) const;

	// asdfadsf
};

