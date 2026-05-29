#pragma once
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

static const int MAP_SIZE = 20;
static const int COLLECTABLE_ITEM = 10;
class Map
{
private:
	char grid[MAP_SIZE][MAP_SIZE]; // Map 20 by 20

	bool isMapLoaded; // TRUE once a valid map is held

	int startRow; // row of 's'
	int startCol; // col of 's'
	int exitRow; // row of 'x'
	int exitCol; // col of 'x'
public:
	Map();
	
	// reference error message to display in Manager
	bool LoadFromFile(const string& filename, string& error); // return TRUE if load map from file using file name
	
	char GetCell(int row, int col) const;
	void SetCell(int row, int col, char c);

	void GetStartPosition(int& row, int& col) const;
	void GetExitPosition(int& row, int& col) const;

	bool IsMapLoaded() const; // return TRUE if valid map is loaded

	bool ValidateMap(string& error); // return TRUE if it is a valid map

	void Display() const; // display the map
};
