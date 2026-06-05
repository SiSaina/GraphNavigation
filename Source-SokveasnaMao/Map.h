/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : Map.h

Description:
	Map class that represents a 20 by 20 grid map loaded from a text file
***************************************************************************/

#pragma once
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

/*
============================================================
Map Class
============================================================

Purpose:
	- Represents a 20 by 20 grid map loaded from a text file.
Used by:
	- GraphManager class for loading, validating, and displaying the map.
	- GraphTools class for constructing a graph from the map.
	- PathFinder class for A* pathfinding using the map.
============================================================
*/

static const int MAP_SIZE = 20; // size of the map (20 by 20)
static const int COLLECTABLE_ITEM = 10; // number of collectable items (a to j)

class Map
{
private:
	/*
	Attributes:
		grid				: 2D array (20x20) representing the map, where each cell can contain:
			- 's' for start
			- 'x' for exit
			- 'a' to 'j' for collectable items
			- 'w' for wall
			- 'p' for path (used in A* path display)
			- '.' for empty space
		isMapLoaded			: boolean flag indicating whether a valid map is currently loaded.
		startRow, startCol	: store the position of the start cell ('s').
		exitRow, exitCol	: store the position of the exit cell ('x').
	*/
	char grid[MAP_SIZE][MAP_SIZE]; // Map 20 by 20

	bool isMapLoaded; // TRUE once a valid map is held

	int startRow; // row of 's'
	int startCol; // col of 's'
	int exitRow; // row of 'x'
	int exitCol; // col of 'x'
public:
	// default constructor that initializes an empty map with '.' and sets isMapLoaded to FALSE
	Map();
	
	/*
	Function: LoadFromFile
	Purpose:
		Loads a map from a text file and validates it.
	Parameters:
		filename: the name of the file to load the map from
		error: reference to a string to store any error messages
	Returns:
		TRUE if the map is loaded and valid, FALSE otherwise
	*/
	bool LoadFromFile(const string& filename, string& error);
	
	/*
	Function: GetCell and SetCell
	Purpose:
		Gets or sets the value of a specific cell in the map.
	Parameters:
		row: the row index of the cell
		col: the column index of the cell
		c: the character to set the cell to (only for SetCell)
	Returns:
		The character at the specified cell (only for GetCell)
	*/
	char GetCell(int row, int col) const;
	void SetCell(int row, int col, char c);

	/*
	Function: SetStartPosition and SetExitPosition
	Purpose:
		Sets the position of the start cell ('s') and exit cell ('x') in the map.
	Parameters:
		row: reference to an integer to store the row index of the start/exit cell
		col: reference to an integer to store the column index of the start/exit cell
	*/
	void SetStartPosition(int& row, int& col) const;
	void SetExitPosition(int& row, int& col) const;

	// helper function
	bool IsMapLoaded() const; // return TRUE if valid map is loaded

	/*
	Function: ValidateMap
	Purpose:
		Validates the loaded map based on specific rules:
			1. Only valid characters ('s', 'x', 'a' to 'j', 'w', 'p', '.') are allowed.
			2. Exactly one start cell ('s') must be present.
			3. Exactly one exit cell ('x') must be present.
			4. Exactly 10 collectable items ('a' to 'j') must be present.
	Parameters:
		error: reference to a string to store any error messages encountered during validation
	Returns:
		TRUE if the map is valid according to the rules, FALSE otherwise
	*/
	bool ValidateMap(string& error); // return TRUE if it is a valid map

	// display map in a 20 by 20 grid format to the console
	void DisplayMap() const;
};
