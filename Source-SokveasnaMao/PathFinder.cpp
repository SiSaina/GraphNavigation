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
	vector<Cell> validNeighbours;

	// all row and col direction: NW, N, NE, W, E, SW, S, SE
	const int directionRow[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int directionCol[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	int currentRow = current.GetRow();
	int currentCol = current.GetCol();

	for (int i = 0;i < 8;i++) {
		// compute neighbour position
		int newRow = currentRow + directionRow[i];
		int newCol = currentCol + directionCol[i];

		// skip neighbour if it lies outside the map boundaries
		if (newRow < 0 || newRow >= MAP_SIZE || newCol < 0 || newCol >= MAP_SIZE)continue;

		// skip wall neighbour
		if (map->GetCell(newRow, newCol) == 'w') continue;

		// cornor cutting prevention
		// if wall then the corner is blocked
		bool isDiagonal = (directionRow[i] != 0) && (directionCol[i] != 0);
		if (isDiagonal) {
			// check the two cardinal directions that form this diagonal
			bool cardinalRowBlocked = (map->GetCell(currentRow + directionRow[i], currentCol) == 'w');
			bool cardinalColBlocked = (map->GetCell(currentRow, currentCol + directionCol[i]) == 'w');
			// if either cardinal direction is blocked, then this diagonal neighbour is not walkable
			if (cardinalRowBlocked || cardinalColBlocked) continue;
		}

		// g cost: euclidean distance of this one step
		Cell neighbourCell(newRow, newCol, 0.0, 0.0, -1, -1); // temporary cell to compute g and h, parent will be set later when pushing to open list
		
		// G cost of step taking from current cell to neighbour cell
		double stepGCost = GetEuclideanDistance(current, neighbourCell);
		// new g cost = current g + step g
		double newGCost = current.GetG() + stepGCost;
		// h cost: manhattan distance to goal
		double newHCost = GetManhattanDistance(neighbourCell, goal);

		// create neighboour cell and store current cell as its parent
		validNeighbours.emplace_back(newRow, newCol, newGCost, newHCost, currentRow, currentCol);
	}
	return validNeighbours;
}

/*==================A Star========================*/
void PathFinder::AStar(Map* map, pair<int, int> startPosition, pair<int, int> endPosition) {
	// create goal cell used for heuristic calculations
	Cell goalCell(endPosition.first, endPosition.second, 0.0, 0.0, -1, -1);

	// initialize search structure
	InitializeSearch(startPosition, goalCell);

	// loop till all reachable cells have been explored
	while (!OpenList.empty()) {
		// retrieve cell with lowest f-cost
		// cause the priority queue is ordered by f-cost
		// so the current cell is always the most promising one
		Cell currentCell = OpenList.top();
		OpenList.pop();

		// skip the cell if its has already been fully processed
		if (ClosedList.count(currentCell)) continue;

		// skip outdated entry if a cheaper path was found later
		pair<int, int> position = make_pair(currentCell.GetRow(), currentCell.GetCol());
		if (currentCell.GetG() > gCost[position] + 1e-9) continue;

		// mark current cell as explored
		ClosedList.insert(currentCell);

		// check if destination has been reach
		if (currentCell.GetRow() == endPosition.first && currentCell.GetCol() == endPosition.second) {
			ReconstructPath(startPosition, endPosition);
			return;
		}

		// explored neighbouring cells
		ProcessNeighbours(map, currentCell, goalCell);
	}
	// if OpenList reach no exit mean no path
}

/*==================Find Path========================*/
bool PathFinder::FindPath(Map* map, pair<int, int> startCell, pair<int, int> endCell) {
	// reset all state so FindPath can be called multiple times
	ClosedList = set<Cell>();
	while (!OpenList.empty()) OpenList.pop();
	pathAStar.clear();
	gCost.clear();
	isPathFound = false;

	// perform A* search
	AStar(map, startCell, endCell);
	return isPathFound;
}

/*==================Path Found========================*/
bool PathFinder::PathFound() const
{
	return isPathFound;
}

/*==================GetPath========================*/
const vector<pair<int, int>>& PathFinder::GetPath() const
{
	return pathAStar;
}

/*==================Reconstruct Path========================*/
void PathFinder::ReconstructPath(pair<int, int> startPosition, pair<int, int> endPosition)
{
	int currentRow = endPosition.first;
	int currentCol = endPosition.second;

	// reconstruct path by following parent links backwards
	while (currentRow != startPosition.first || currentCol != startPosition.second) {
		pathAStar.push_back({ currentRow, currentCol });

		// check this position in ClosedList to get its parent
		set<Cell>::iterator it = ClosedList.find(Cell(currentRow, currentCol, 0.0, 0.0, -1, -1));
		if (it == ClosedList.end()) break;

		// move to parent cell
		currentRow = it->GetParentRow();
		currentCol = it->GetParentCol();
	}

	// add starting position
	pathAStar.push_back(startPosition);

	// reverse to obtain start to goal order
	reverse(pathAStar.begin(), pathAStar.end());

	isPathFound = true;
}

/*==================Process Neighbours========================*/
void PathFinder::ProcessNeighbours(Map* map, const Cell& currentCell, const Cell& goalCell)
{
	vector<Cell> neighbours = GetNeighbours(map, currentCell, goalCell);

	for (int i = 0;i < neighbours.size(); i++) {
		Cell neighbour = neighbours[i];

		// skip explored cells
		if (ClosedList.count(neighbour)) continue;

		pair<int, int> neighbourPosition = make_pair(neighbour.GetRow(), neighbour.GetCol());

		// check whether neighbour has been visited before
		bool firstVisit = (gCost.find(neighbourPosition) == gCost.end());

		// check if current route is cheaper
		bool betterPath = (!firstVisit && neighbour.GetG() < gCost[neighbourPosition]);

		// update cheapest known cost
		if (firstVisit || betterPath) {
			gCost[neighbourPosition] = neighbour.GetG();
			OpenList.push(neighbour);
		}
	}
}

/*==================Initialize Search========================*/
void PathFinder::InitializeSearch(pair<int, int> startPosition, const Cell& goalCell)
{
	// create temp start cell to calculate initial heuristic value
	Cell tempStartCell = Cell(startPosition.first, startPosition.second, 0.0, 0.0, -1, -1);

	// calculate heuristic cost from start to goal
	double hCost = GetManhattanDistance(tempStartCell, goalCell);

	// create actual start node with g = 0, and h = estimated distance to goal
	Cell startCell(startPosition.first, startPosition.second, 0.0, hCost, -1, -1);

	// record the cheapest known cost to reach start cell
	gCost[startPosition] = 0.0;

	// insert start cell into open list
	OpenList.push(startCell);
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
	for (int i = 1;i < pathAStar.size() - 1;i++) {
		display[pathAStar[i].first][pathAStar[i].second] = 'p';
	}
	cout << endl;

	// print the map with path overlay
	for (int i = 0;i < MAP_SIZE;i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			cout << display[i][j];
		}
		cout << endl;
	}

	// =========== For Extension =========== 
	// compute total total moment path cost
	double totalCost = 0.0;
	for (int i = 1;i < pathAStar.size();i++) {
		int directionRow = pathAStar[i].first - pathAStar[i - 1].first;
		int directionCol = pathAStar[i].second - pathAStar[i - 1].second;

		// diagonal move cost sqrt(2), straight move cost 1
		totalCost += (directionRow && directionCol) ? sqrt(2.0) : 1.0;
	}

	cout << endl;
	cout << "Path step: " << (pathAStar.size() - 1) << endl;
	cout << "Path cost: " << fixed << setprecision(2) << totalCost << endl;
	cout << "Nodes closed (visited): " << ClosedList.size() << endl;
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
	for (int i = 1;i < pathAStar.size() - 1;i++) {
		grid[pathAStar[i].first][pathAStar[i].second] = 'p';
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
