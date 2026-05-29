#include "Map.h"
#include <iostream>

Map::Map() : isMapLoaded(false), startRow(-1), startCol(-1), exitRow(-1), exitCol(-1) {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			grid[i][j] = '.';
		}
	}
}

bool Map::LoadFromFile(const string& filename, string& error) {
	// reset these member variable
	isMapLoaded = false;
	startRow = startCol = -1;
	exitRow = exitCol = -1;
	
	ifstream file(filename);
	// if file is not open
	if (!file.is_open()) {
		error = "LoadFromFile error: Please check the filename";
		return false;
	}

	string line;
	int row = 0;

	while (getline(file, line)) {
		// strip any trailing carriage return
		if (!line.empty() && line.back() == '\r') line.pop_back();
		
		if (row >= MAP_SIZE) {
			// extra non-empty lines are an error and blank line are ignored
			if (!line.empty()) {
				error = "LoadFromFile error: map has more then" + to_string(MAP_SIZE) + " rows";
				return false;
			}
			continue;
		}

		if (static_cast<int>(line.size()) != MAP_SIZE) {
			error = "LoadFromFile error: " + to_string(row) + " has " + to_string(line.size()) + " characters (expected " + to_string(MAP_SIZE) + ").";
			return false;
		}
		for (int col = 0;col < MAP_SIZE; col++) {
			grid[row][col] = line[col];
		}
		row++;
	}
	if (row != MAP_SIZE) {
		error = "LoadFromFile error: " + to_string(row) + " rows (expected " + to_string(MAP_SIZE) + ").";
		return false;
	}

	// validate the map
	if (!ValidateMap(error)) return false;

	isMapLoaded = true;
	return true;
}

char Map::GetCell(int row, int col) const
{
	return grid[row][col];
}

void Map::SetCell(int row, int col, char c)
{
	grid[row][col] = c;
}

void Map::GetStartPosition(int& row, int& col) const
{
	row = startRow;
	col = startCol;
}

void Map::GetExitPosition(int& row, int& col) const
{
	row = exitRow;
	col = exitCol;
}

bool Map::IsMapLoaded() const
{
	return isMapLoaded;
}

bool Map::ValidateMap(string& error)
{
	// to record the valid character in the map
	const string VALID_CHARS = "abcdefghijpswx.";

	// to record the start, exit and collectable variable
	int startCount = 0;
	int exitCount = 0;
	int collectableCount = 0;

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE;j++) {
			char ch = grid[i][j];

			// rule 1: only recognised symbols are allow
			if (VALID_CHARS.find(ch) == string::npos) {
				error = "ValidateMap error: invalid character " + string(1, ch) + "' at row " + to_string(i) + ", col " + to_string(j);
				return false;
			}

			// count special character
			if (ch == 's') {
				startCount++;
				startRow = i;
				startCol = j;
			}
			else if (ch == 'x') {
				exitCount++;
				exitRow = i;
				exitCol = j;
			}
			else if (ch >= 'a' && ch <= 'j') {
				collectableCount++;
			}
		}
	}

	// rule 2: only 1 start cell allow
	if (startCount == 0) {
		error = "ValidateMap error: this map has no start cell";
		return false;
	}
	if (startCount > 1) {
		error = "ValidateMap error: this map has " + to_string(startCount) + " start cell";
		return false;
	}

	// rule 3: only 1 exit cell allow
	if (exitCount == 0) {
		error = "ValidateMap error: this map has no exit cell";
		return false;
	}
	if (exitCount > 1) {
		error = "ValidateMap error: this map has " + to_string(exitCount) + " exit cell";
		return false;
	}

	// rule 4: only 10 collectable item allow
	if (collectableCount != COLLECTABLE_ITEM) {
		error = "ValidateMap error: this map has " + to_string(collectableCount) + " collectable";
		return false;
	}

	return true;
}

void Map::Display() const {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
	cout << endl;
}