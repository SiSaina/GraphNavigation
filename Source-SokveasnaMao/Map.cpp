#include "Map.h"
#include <iostream>

/*==================Default Constructor=========================*/
Map::Map() : isMapLoaded(false), startRow(-1), startCol(-1), exitRow(-1), exitCol(-1) {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0;j < MAP_SIZE;j++) {
			grid[i][j] = '.';
		}
	}
}

/*==================Load From File========================*/
bool Map::LoadFromFile(const string& filename, string& error) {
	// reset these member variable
	isMapLoaded = false;
	startRow = startCol = -1;
	exitRow = exitCol = -1;
	
	ifstream file(filename);
	// check if file is open successfully
	if (!file.is_open()) {
		error = "LoadFromFile error: Please check the filename";
		return false;
	}

	// create a string variable to store each line and a row counter
	string line;
	int row = 0;

	// read file line by line
	while (getline(file, line)) {
		// strip any trailing carriage return
		if (!line.empty() && line.back() == '\r') line.pop_back();
		
		// check if the current line exceeds the expected row size
		if (row >= MAP_SIZE) {
			// extra non-empty lines are an error and blank line are ignored
			if (!line.empty()) {
				error = "LoadFromFile error: map has more then" + to_string(MAP_SIZE) + " rows";
				return false;
			}
			continue;
		}

		// validate column size of the current row
		if (static_cast<int>(line.size()) != MAP_SIZE) {
			error = "LoadFromFile error: " + to_string(row) + " has " + to_string(line.size()) + " characters (expected " + to_string(MAP_SIZE) + ").";
			return false;
		}
		// copy row into grid
		for (int col = 0;col < MAP_SIZE; col++) {
			grid[row][col] = line[col];
		}
		row++;
	}
	// ensure correct number of rows
	if (row != MAP_SIZE) {
		error = "LoadFromFile error: " + to_string(row) + " rows (expected " + to_string(MAP_SIZE) + ").";
		return false;
	}

	// validate the map
	if (!ValidateMap(error)) return false;

	// if we reach here, the map is loaded and valid
	isMapLoaded = true;
	return true;
}

/*==================Get Cell========================*/
char Map::GetCell(int row, int col) const
{
	return grid[row][col];
}
/*==================Set Cell========================*/
void Map::SetCell(int row, int col, char c)
{
	grid[row][col] = c;
}
/*==================Set Start Position========================*/
void Map::SetStartPosition(int& row, int& col) const
{
	row = startRow;
	col = startCol;
}
/*==================Set Exit Position========================*/
void Map::SetExitPosition(int& row, int& col) const
{
	row = exitRow;
	col = exitCol;
}
/*==================Is Map Loaded========================*/
bool Map::IsMapLoaded() const
{
	return isMapLoaded;
}

/*==================Validate Map========================*/
bool Map::ValidateMap(string& error)
{
	// store the valid character in the map
	const string VALID_CHARS = "abcdefghijpswx.";

	// store the start, exit and collectable variable
	int startCount = 0;
	int exitCount = 0;
	int collectableCount = 0;

	// scan the map and validate each cell, count start, exit and collectable
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE;j++) {
			// get the character at the current cell
			char ch = grid[i][j];

			// rule 1: only recognised symbols are allow
			if (VALID_CHARS.find(ch) == string::npos) {
				error = "ValidateMap error: invalid character " + string(1, ch) + "' at row " + to_string(i) + ", col " + to_string(j);
				return false;
			}

			// scan start node and store its position
			if (ch == 's') {
				startCount++;
				startRow = i;
				startCol = j;
			}
			// scan exit node and store its position
			else if (ch == 'x') {
				exitCount++;
				exitRow = i;
				exitCol = j;
			}
			// scan collectable item
			else if (ch >= 'a' && ch <= 'j') {
				collectableCount++;
			}
		}
	}

	// rule 2: only 1 start cell allow
	if (startCount != 1) {
		error = "ValidateMap error: map must contain exactly 1 start node";
		return false;
	}

	// rule 3: only 1 exit cell allow
	if (exitCount != 1) {
		error = "ValidateMap error: map must contain exactly 1 exit node";
		return false;
	}

	// rule 4: only 10 collectable item allow
	if (collectableCount != COLLECTABLE_ITEM) {
		error = "ValidateMap error: this map has " + to_string(collectableCount) + " collectable";
		return false;
	}

	return true;
}

/*==================Display Map========================*/
void Map::DisplayMap() const {
	// display the map in a 20 by 20 grid format to the console
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
	cout << endl;
}