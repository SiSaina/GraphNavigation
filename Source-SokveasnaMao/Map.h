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

static const int MAP_SIZE = 20; // size of the map (20 by 20)
static const int COLLECTABLE_ITEM = 10; // number of collectable items (a to j)

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
class Map
{
private:
	// 2D array (20x20) representing the map
	char grid[MAP_SIZE][MAP_SIZE];

	// check whether valid is currently loaded
	bool isMapLoaded;

	// store row of start cell
	int startRow;
	// store col of start cell
	int startCol;
	// store row of exit cell
	int exitRow;
	// store col of exit cell
	int exitCol;
public:
	// default constructor that initializes an empty map with '.' and sets isMapLoaded to FALSE
	Map();
	
	/*
	Function: LoadFromFile
	Purpose:
		- Loads a map from a text file and validates it.
	Parameters:
		- filename: the name of the file to load the map from
		- error: reference to a string to store any error messages
	Returns:
		- TRUE if the map is loaded and valid, FALSE otherwise
	*/
	bool LoadFromFile(const string& filename, string& error);
	
	/*
	Function: GetCell
	Purpose:
		- Gets value of a specific cell in the map
	Parameters:
		- row: the row of cell
		- col: the col of cell
	Returns:
		- character at the specified cell
	*/
	char GetCell(int row, int col) const;

	/*
	Function: SetCell
	Purpose:
		- updates the value store in a specific cell
	Parameters:
		- row: the row of cell
		- col: the col of cell
		- c: the character to set the cell
	*/
	void SetCell(int row, int col, char c);

	/*
	Function: SetStartPosition
	Purpose:
		- Sets start cell ('x') position
	Parameters:
		- row: reference integer to store row index of start cell
		- col: reference integer to store col index of start cell
	*/
	void SetStartPosition(int& row, int& col) const;
	
	/*
	Function: SetStartPosition and SetExitPosition
	Purpose:
		- Sets exit cell ('x') position
	Parameters:
		- row: reference integer to store row index of start cell
		- col: reference integer to store col index of start cell
	*/
	void SetExitPosition(int& row, int& col) const;

	/*
	Function: IsMapLoaded
	Purpose:
		- check if valid map is currently loaded
	Return:
		- TRUE if a map is loaded, FALSE otherwise
	*/
	bool IsMapLoaded() const;

	/*
	Function: ValidateMap
	Purpose:
		- Validates the loaded map based on specific rules:
			1. Only valid characters ('s', 'x', 'a' to 'j', 'w', 'p', '.') are allowed.
			2. Exactly one start cell ('s') must be present.
			3. Exactly one exit cell ('x') must be present.
			4. Exactly 10 collectable items ('a' to 'j') must be present.
	Parameters:
		- error: reference to a string to store any error messages encountered during validation
	Returns: TRUE if the map is valid according to the rules, FALSE otherwise
	*/
	bool ValidateMap(string& error); // return TRUE if it is a valid map

	// display map in a 20 by 20 grid format to the console
	void DisplayMap() const;
};
