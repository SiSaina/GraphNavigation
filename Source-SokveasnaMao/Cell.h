#pragma once
 /*
============================================================
						 Cell Class
============================================================
 Purpose:
 Represent a single node (cell) in the A* path finding algorithm

 Each cell stores:
	 - position in grid (row, col)
	 - parent position (parentRow, parentCol) for path reconstruction

 Cost values used in A*:
	 - g: cost from start to this cell (Euclidean distance)
	 - h: Manhattan distance to goal (heuristic)
	 - f: total cost (f = g + h)
 
 This class is used by:
  - AStar class to manage open and closed sets
	- Priority queue for selecting next cell to explore
	- Set for tracking visited cells
 */
class Cell
{
private:
	int row, col; // position in grid
	int parentRow, parentCol; // parent cell used for reconstruct path

	double g; // Euclidean cost from start
	double h; // Manhattan heuristic
	double f; // f = g + h
public:
	// default constructor initializes to default values
	Cell();
	// parameterized constructor to initialize all values
	Cell(int _row, int _col, double _g, double _h, int _parentRow, int _parentCol);

	// getter and setter methods for all member variables
	int GetRow() const { return row; }; // return row index
	int GetCol() const { return col; }; // return column index
	double GetG() const { return g; }; // return g cost
	double GetH() const { return h; }; // return h cost
	double GetF() const { return f; }; // return f cost
	int GetParentRow() const { return parentRow; }; // return parent row index
	int GetParentCol() const { return parentCol; }; // return parent column index

	void SetRow(int _row) { row = _row; } // set row index
	void SetCol(int _col) { col = _col; } // set column index
	void SetG(double _g) { g = _g; f = g + h; } // set g cost and update f
	void SetH(double _h) { h = _h; f = g + h; } // set h cost and update f
	void SetF(double _f) { f = _f; } // set f cost
	void SetParentRow(int _parentRow) { parentRow = _parentRow; } // set parent row index
	void SetParentCol(int _parentCol) { parentCol = _parentCol; } // set parent column index
	
	// used for set<cell>
	// ensure cells are ordered by row, then column for uniqueness in sets
	bool operator<(const Cell& other) const;

	// used for priority queue
	// return TRUE if this cell has higher priority (lower f, then lower g)
	bool operator>(const Cell& other) const;

	// check if two cells are the same (same row and column)
	bool operator==(const Cell& other) const;
};

