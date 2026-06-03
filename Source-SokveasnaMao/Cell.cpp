#include "Cell.h"

/*
	============================================================
	Cell Class Implementation
	============================================================

	Purpose:
	Implements the constructors and comparison operators for
	the Cell class used in A* pathfinding.

	Each cell represents a node in the grid and is used in:
	- open list (priority queue / set)
	- closed list
	- path reconstruction
*/

/*
	default constructor initializes all member variables to default values:
	- row and col to 0 (top-left corner)
	- g, h, f to 0.0 (no cost)
	- parentRow and parentCol to -1 (no parent)
*/
Cell::Cell(): row(0), col(0), g(0.0), h(0.0), f(0.0), parentRow(-1), parentCol(-1) { }

/*
	parameterized constructor initializes all member variables to provided values:
	- row and col to specified position in grid
	- g and h to specified cost values
	- f is calculated as g + h
	- parentRow and parentCol to specified parent position for path reconstruction
*/
Cell::Cell(int _row, int _col, double _g, double _h, int _parentRow, int _parentCol)
    : row(_row), col(_col), g(_g), h(_h), f(_g + _h), parentRow(_parentRow), parentCol(_parentCol) { }

/*
	operator< is used for ordering cells in a set (e.g., closed list) to ensure uniqueness.
	It orders cells first by row, then by column. This allows us to store cells in a set
	and quickly check if a cell has been visited (closed) based on its position in the grid.
	For example, Cell(1, 2) < Cell(1, 3) is true because they are in the same row but different columns.
	Cell(1, 2) < Cell(2, 1) is true because row 1 is less than row 2.
*/
bool Cell::operator<(const Cell& other) const
{
	if (row != other.row) return row < other.row;
	return col < other.col;
}

/*
	operator> is used for ordering cells in a priority queue (e.g., open list) to determine which cell has higher priority.
	In A*, the cell with the lowest f cost has the highest priority. If two cells have the same f cost, the one with the lower g cost (closer to start) has higher priority.
	For example, Cell(1, 2, g=5, h=10) > Cell(1, 3, g=3, h=12) is true because Cell(1, 2) has a lower f cost (15) than Cell(1, 3) (15), but Cell(1, 2) has a higher g cost (5 vs 3).
*/
bool Cell::operator>(const Cell& other) const {
	if (f != other.f) return f > other.f;
	return g < other.g;
}

/*
	operator== checks if two cells are the same based on their position in the grid (row and column).
	This is used to determine if a cell has already been visited or if we have reached the goal.
	For example, Cell(1, 2) == Cell(1, 2) is true, but Cell(1, 2) == Cell(2, 1) is false.
*/
bool Cell::operator==(const Cell& other) const
{
	return row == other.row && col == other.col;
}
