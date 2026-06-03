/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : Cell.h

Description:
Defines the Cell class used by the A* pathfinding algorithm.
***************************************************************************/

/*
============================================================
Cell Class
============================================================

Purpose:
- Represents a single node (cell) in the A* pathfinding algorithm.

Used by:
- A* algorithm
- Open list (priority queue)
- Closed list (set)
============================================================
*/
#pragma once
 
class Cell
{
private:
	/*
	Purpose of attributes:
	row, col:
		- Store the cell's position in the grid.
	parentRow, parentCol:
		- Store the position of the parent cell used for path reconstruction.
	g:
		- The cost from the start cell to this cell (g cost).
	h:
		- The heuristic cost estimate from this cell to the goal (h cost).
	f:
		- The total cost (f = g + h) used for prioritization in A*.
	*/
	int row, col; // position in grid
	int parentRow, parentCol; // parent cell used for path reconstruction

	double g; // Euclidean cost from start
	double h; // Manhattan heuristic
	double f; // f = g + h
public:
	/*
	Purpose:
		Default constructor that initializes a Cell with default values.
	*/
	Cell();

	/*
	Purpose:
		Parameterized constructor to initialize all attributes.

	Parameters:
		_row        - row index
		_col        - column index
		_g          - cost from start
		_h          - heuristic cost
		_parentRow  - parent row index
		_parentCol  - parent column index
	*/
	Cell(int _row, int _col, double _g, double _h, int _parentRow, int _parentCol);

	/*
	Getters:
		Return stored values of the Cell
	*/
	int GetRow() const { return row; }; // return row index
	int GetCol() const { return col; }; // return column index
	double GetG() const { return g; }; // return g cost
	double GetH() const { return h; }; // return h cost
	double GetF() const { return f; }; // return f cost
	int GetParentRow() const { return parentRow; }; // return parent row index
	int GetParentCol() const { return parentCol; }; // return parent column index
	
	/*
	Setters:
		Update values of the Cell.
		Note: updating g or h automatically updates f = g + h
	*/
	void SetRow(int _row) { row = _row; } // set row index
	void SetCol(int _col) { col = _col; } // set column index
	void SetG(double _g) { g = _g; f = g + h; } // set g cost and update f
	void SetH(double _h) { h = _h; f = g + h; } // set h cost and update f
	void SetF(double _f) { f = _f; } // set f cost
	void SetParentRow(int _parentRow) { parentRow = _parentRow; } // set parent row index
	void SetParentCol(int _parentCol) { parentCol = _parentCol; } // set parent column index
	
	/*
	============================================================
	Operator: <
	Purpose:
		Used for ordering cells in sets (closed list).

	Comparison Rule:
		1. Compare row
		2. Compare column

	Parameter:
		other - another Cell to compare with
	Returns:
		true  - this Cell is "less than" the other Cell
	============================================================
	*/
	bool operator<(const Cell& other) const;

	/*
	============================================================
	Operator: >
	Purpose:
		Used in priority queue for A* open list.

	Priority Rule:
		1. Lower f cost has higher priority
		2. If f is equal, lower g cost wins
	============================================================
	*/
	bool operator>(const Cell& other) const;

	/*
	============================================================
	Operator: ==
	Purpose:
		Checks if two cells are at the same grid position.

	Returns:
		true  - same (row, col)
		false - otherwise
	============================================================
	*/
	bool operator==(const Cell& other) const;
};

