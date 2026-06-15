/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : PathFinder.cpp

Description:
	Implementation of PathFinder class and its algorithm
***************************************************************************/

#include "PathFinder.h"

/*==================Get Euclidean Distance========================*/
double PathFinder::GetEuclideanDistance(const Cell& a, const Cell& b) const
{
	// formula: d = sqrt((i1 - i2)^2 + (j1 - j2)^2)
	// use double to avoid precision loss in sqrt
	double dI = static_cast<double>(a.GetRow() - b.GetRow());
	double dJ = static_cast<double>(a.GetCol() - b.GetCol());

	return sqrt(dI * dI + dJ * dJ);
}

/*==================Get Manhattan Distance========================*/
double PathFinder::GetManhattanDistance(const Cell& a, const Cell& b) const 
{
	// formula: d = |i1 - i2| + |j1 - j2|
	return static_cast<double>(abs(a.GetRow() - b.GetRow()) +
							   abs(a.GetCol() - b.GetCol()));
}

/*==================Get Neighbours========================*/
vector<Cell> PathFinder::GetNeighbours(Map* map, const Cell& current, const Cell& goal) {
	// result vector to store valid neighbours
	vector<Cell> result;

	// all row and col direction: NW, N, NE, W, E, SW, S, SE
	const int directionRow[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int directionCol[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	int row = current.GetRow();
	int col = current.GetCol();

	for (int i = 0;i < 8;i++) {
		// compute neighbour position
		int newRow = row + directionRow[i];
		int newCol = col + directionCol[i];

		// bound checks
		if (newRow < 0 || newRow >= MAP_SIZE || newCol < 0 || newCol >= MAP_SIZE)continue;

		// wall check
		if (map->GetCell(newRow, newCol) == 'w') continue;

		// cornor cutting prevention
		// if wall then the corner is blocked
		bool isDiagonal = (directionRow[i] != 0) && (directionCol[i] != 0);
		if (isDiagonal) {
			// check the two cardinal directions that form this diagonal
			bool cardinalRowBlocked = (map->GetCell(row + directionRow[i], col) == 'w');
			bool cardinalColBlocked = (map->GetCell(row, col + directionCol[i]) == 'w');
			// if either cardinal direction is blocked, then this diagonal neighbour is not walkable
			if (cardinalRowBlocked || cardinalColBlocked) continue;
		}

		// g cost: euclidean distance of this one step
		Cell neighbourCell(newRow, newCol, 0.0, 0.0, -1, -1); // temporary cell to compute g and h, parent will be set later when pushing to open list
		
		// use double to avoid precision loss in sqrt
		double stepG = GetEuclideanDistance(current, neighbourCell);
		// new g cost = current g + step g
		double newG = current.GetG() + stepG;

		// h cost: manhattan distance to goal
		double newH = GetManhattanDistance(neighbourCell, goal);

		// build full cost neightnour with parent = current
		result.emplace_back(newRow, newCol, newG, newH, row, col);
	}
	return result;
}

/*==================A Star========================*/
void PathFinder::AStar(Map* map, pair<int, int> startPosition, pair<int, int> endPosition) {
	// create goal cell used for heuristic calculations
	Cell goal(endPosition.first, endPosition.second, 0.0, 0.0, -1, -1);

	// create temp start cell to calculate initial heuristic value
	Cell tempStartCell = Cell(startPosition.first, startPosition.second, 0.0, 0.0, -1, -1);
	
	// calculate heuristic cost from start to goal
	double hCost = GetManhattanDistance(tempStartCell, goal);

	// create actual start node with g = 0, and h = calculated heuristic
	Cell startCell(startPosition.first, startPosition.second, 0.0, hCost, -1, -1);

	// record best known cost to reach start cell
	cost[startPosition] = 0.0;

	// insert start cell into open list
	OpenList.push(startCell);

	// loop till all reachable cells have been explored
	while (!OpenList.empty()) {
		// cause the priority queue is ordered by f-cost
		// so the current cell is always the most promising one
		// retrieve cell with lowest f-cost
		Cell current = OpenList.top();
		OpenList.pop();

		// skip the cell if its has already been fully processed
		if (ClosedList.count(current)) continue;

		// skip outdated entry if a cheaper path was found later
		pair<int, int> position = make_pair(current.GetRow(), current.GetCol());
		if (current.GetG() > cost[position] + 1e-9) continue;

		// mark current cell as explored
		ClosedList.insert(current);

		// check if destination has been reach
		if (current.GetRow() == endPosition.first && current.GetCol() == endPosition.second) {
			int currentRow = endPosition.first;
			int currentCol = endPosition.second;
		
			// reconstruct path by following parent links backwards
			while (currentRow != startPosition.first || currentCol != startPosition.second) {
				path.push_back({ currentRow, currentCol });

				// check this position in ClosedList to get its parent
				set<Cell>::iterator it = ClosedList.find(Cell(currentRow, currentCol, 0.0, 0.0, -1, -1));
				if (it == ClosedList.end()) break;

				// move to parent cell
				int parentRow = it->GetParentRow();
				int parentCol = it->GetParentCol();
				currentRow = parentRow;
				currentCol = parentCol;
			}

			// add starting position
			path.push_back(startPosition);

			// reverse to obtain start to goal order
			reverse(path.begin(), path.end());

			found = true;
			return;
		}

		// generate and process all valid neighbour cell
		for (const Cell& neighbour : GetNeighbours(map, current, goal)) {
			// skip explored cells
			if (ClosedList.count(neighbour)) continue;

			pair<int, int> neighbourPosition = make_pair(neighbour.GetRow(), neighbour.GetCol());

			// check whether this neighbour has been visited before
			bool firstVisit = (cost.find(neighbourPosition)) == cost.end();

			// check if current route provides a cheaper path
			bool betterPath = (!firstVisit && neighbour.GetG() < cost[neighbourPosition]);

			// update best cost and add neighbour to open list
			if (firstVisit || betterPath) {
				cost[neighbourPosition] = neighbour.GetG();
				OpenList.push(neighbour);
			}
		}
	}
	// if OpenList reach no exit mean no path
}

/*==================Find Path========================*/
bool PathFinder::FindPath(Map* map, pair<int, int> start, pair<int, int> end) {
	// reset all state so FindPath can be called multiple times
	ClosedList = set<Cell>();
	while (!OpenList.empty()) OpenList.pop();
	path.clear();
	cost.clear();
	found = false;

	// perform A* search
	AStar(map, start, end);
	return found;
}

/*==================Path Found========================*/
bool PathFinder::PathFound() const
{
	return found;
}

/*==================GetPath========================*/
const vector<pair<int, int>>& PathFinder::GetPath() const
{
	return path;
}

/*==================Display Path========================*/
void PathFinder::DisplayPath(Map* map) const {
	// build a display copy so the Map object is never modified
	char display[MAP_SIZE][MAP_SIZE]{};
	for (int i = 0;i < MAP_SIZE;i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			display[i][j] = map->GetCell(i, j);
		}
	}

	// mark intermediate cells 'p' (skip index 0 = start, last = exit)
	for (int i = 1;i < path.size() - 1;i++) {
		display[path[i].first][path[i].second] = 'p';
	}
	cout << endl;

	// print the map with path overlay
	for (int i = 0;i < MAP_SIZE;i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			cout << display[i][j];
		}
		cout << endl;
	}

	/*
	- Display path step, cost and total node closed (optional for display)
	- used for debugging and verification

		// compute total total moment path cost
		double totalCost = 0.0;
		for (int i = 1;i < path.size();i++) {
			int directionRow = path[i].first - path[i - 1].first;
			int directionCol = path[i].second - path[i - 1].second;

			// diagonal move cost sqrt(2), straight move cost 1
			totalCost += (directionRow && directionCol) ? sqrt(2.0) : 1.0;
		}

		cout << endl;
		cout << "Path step: " << (path.size() - 1) << endl;
		cout << "Path cost: " << fixed << setprecision(2) << totalCost << endl;
		cout << "Nodes closed (visited): " << ClosedList.size() << endl;
	*/
}

/*==================Save Path========================*/
bool PathFinder::SavePath(Map* map, const string& filename) const {

	// create a copy of the map
	char grid[MAP_SIZE][MAP_SIZE]{};
	
	for (int i = 0;i < MAP_SIZE;i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			grid[i][j] = map->GetCell(i, j);
		}
	}

	// mark path cells with 'p'
	for (int i = 1;i < path.size() - 1;i++) {
		grid[path[i].first][path[i].second] = 'p';
	}

	// open output file
	ofstream file(filename);
	if (!file.is_open()) return false;

	// write grid content to file
	for (int i = 0;i < MAP_SIZE;i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			file << grid[i][j];
		}
		file << endl;
	}
	return true;
}
