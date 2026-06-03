#include "PathFinder.h"

double PathFinder::GetEuclideanDistance(const Cell& a, const Cell& b) const
{
	double dI = static_cast<double>(a.GetRow() - b.GetRow());
	double dJ = static_cast<double>(a.GetCol() - b.GetCol());

	return sqrt(dI * dI + dJ * dJ);

}

double PathFinder::GetManhattanDistance(const Cell& a, const Cell& b) const 
{
	return static_cast<double>(abs(a.GetRow() - b.GetRow() +
							   abs(a.GetCol() - b.GetCol())));
}

vector<Cell> PathFinder::GetNeighbours(Map* map, const Cell& current, const Cell& goal) {
	vector<Cell> result;

	// all row and col direction: N, NE, E, SE, S, SW, W, NW
	const int DR[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int DC[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	int r = current.GetRow();
	int c = current.GetCol();

	for (int i = 0;i < 8;i++) {
		int nr = r + DR[i];
		int nc = c + DC[i];

		// bound checks
		if (nr < 0 || nr >= MAP_SIZE || nc < 0 || nc >= MAP_SIZE)continue;

		// wall check
		if (map->GetCell(nr, nc) == 'w') continue;

		// cornor cutting prevention
		// if wall then the corner is blocked
		bool isDiagonal = (DR[i] != 0) && (DC[i] != 0);
		if (isDiagonal) {
			bool cardinalRowBlocked = (map->GetCell(r + DR[i], c) == 'w');
			bool cardinalColBlocked = (map->GetCell(r, c + DC[i]) == 'w');
			if (cardinalRowBlocked || cardinalColBlocked) continue;
		}

		// g cost: euclidean distance of this one step
		Cell nbCell(nr, nc, 0.0, 0.0, -1, -1); // temp - position only
		double stepG = GetEuclideanDistance(current, nbCell);
		double newG = current.GetG() + stepG;

		// h cost: manhattan distance to goal
		double newH = GetManhattanDistance(nbCell, goal);

		// build full cost neightnour with parent = current
		result.emplace_back(nr, nc, newG, newH, r, c);
	}
	return result;
}

void PathFinder::AStar(Map* map, pair<int, int> startPosition, pair<int, int> endPosition) {
	Cell goal(endPosition.first, endPosition.second, 0.0, 0.0, -1, -1);

	// seed the start cell: g = 0, h = manhattan to exit, no parent
	Cell tempCell = Cell(startPosition.first, startPosition.second, 0.0, 0.0, -1, -1);
	double h0 = GetManhattanDistance(tempCell, goal);
	Cell startCell(startPosition.first, startPosition.second, 0.0, h0, -1, -1);

	cost[startPosition] = 0.0;
	OpenList.push(startCell);

	while (!OpenList.empty()) {
		Cell current = OpenList.top();
		OpenList.pop();

		// already in closed list
		// a better path was finalized earlier
		if (ClosedList.count(current)) continue;

		// a cheaper path was found after this entry was pushed
		auto position = make_pair(current.GetRow(), current.GetCol());
		if (current.GetG() > cost[position] + 1e-9) continue;

		// close this cell
		ClosedList.insert(current);

		// goal test
		if (current.GetRow() == endPosition.first && current.GetCol() == endPosition.second) {
			int currentRow = endPosition.first;
			int currentCol = endPosition.second;
		
			while (currentRow != startPosition.first || currentCol != startPosition.second) {
				path.push_back({ currentRow, currentCol });

				// check this position in ClosedList to get its parent
				auto it = ClosedList.find(Cell(currentRow, currentCol, 0.0, 0.0, -1, -1));
				if (it == ClosedList.end()) break;

				int parentRow = it->GetParentRow();
				int parentCol = it->GetParentCol();
				currentRow = parentRow;
				currentCol = parentCol;
			}
			path.push_back(startPosition);
			reverse(path.begin(), path.end());
			found = true;
			return;
		}

		// expand neighbours
		for (const Cell& nb : GetNeighbours(map, current, goal)) {
			if (ClosedList.count(nb)) continue;

			auto nbPosition = make_pair(nb.GetRow(), nb.GetCol());

			// only push if this is the best path to nbPosition found so far
			bool firstVisit = (cost.find(nbPosition)) == cost.end();
			bool betterPath = (!firstVisit && nb.GetG() < cost[nbPosition]);

			if (firstVisit || betterPath) {
				cost[nbPosition] = nb.GetG();
				OpenList.push(nb);
			}
		}
	}
	// if OpenList reach no exit mean no path
}

bool PathFinder::FindPath(Map* map, pair<int, int> start, pair<int, int> end) {
	// reset all state so FindPath can be called multiple times
	ClosedList = set<Cell>();
	while (!OpenList.empty()) OpenList.pop();
	path.clear();
	cost.clear();
	found = false;

	AStar(map, start, end);
	return found;
}

bool PathFinder::PathFound() const
{
	return found;
}

const vector<pair<int, int>>& PathFinder::GetPath() const
{
	return path;
}

void PathFinder::DisplayPath(Map* map) const {
	// build a display copy so the Map object is never modified
	char display[MAP_SIZE][MAP_SIZE];
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

	for (int i = 0;i < MAP_SIZE;i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			cout << display[i][j];
		}
		cout << endl;
	}

	// compute total euclidea path cost
	double totalCost = 0.0;
	for (int i = 1;i < path.size();i++) {
		int dr = path[i].first - path[i - 1].first;
		int dc = path[i].second - path[i - 1].second;
		totalCost += (dr && dc) ? sqrt(2.0) : 1.0;
	}

	cout << endl;
	cout << "Path step: " << (path.size() - 1) << endl;
	cout << "Path cost: " << fixed << setprecision(2) << totalCost << endl;
	cout << "Nodes closed (visited): " << ClosedList.size() << endl;
}

bool PathFinder::SavePath(Map* map, const string& filename) const {
	char grid[MAP_SIZE][MAP_SIZE];
	for (int i = 0;i < MAP_SIZE;i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			grid[i][j] = map->GetCell(i, j);
		}
	}
	for (int i = 1;i < path.size() - 1;i++) {
		grid[path[i].first][path[i].second] = 'p';
	}

	ofstream file(filename);
	if (!file.is_open()) return false;

	for (int i = 0;i < MAP_SIZE;i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			file << grid[i][j];
		}
		file << endl;
	}
	return true;
}
