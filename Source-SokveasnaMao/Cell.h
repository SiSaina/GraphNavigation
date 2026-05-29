#pragma once
class Cell
{
private:
	int row, col;
	int parentRow, parentCol; // used for reconstruct path

	double g; // Euclidean cost from start
	double h; // Manhattan heuristic
	double f; // f = g + h
public:
	Cell();
	Cell(int _row, int _col, double _g, double _h, int _parentRow, int _parentCol);

	int GetRow() const { return row; };
	int GetCol() const { return col; };
	double GetG() const { return g; };
	double GetH() const { return h; };
	double GetF() const { return f; };
	int GetParentRow() const { return parentRow; };
	int GetParentCol() const { return parentCol; };

	void SetRow(int _row) { row = _row; }
	void SetCol(int _col) { col = _col; }
	void SetG(double _g) { g = _g; f = g + h; }
	void SetH(double _h) { h = _h; f = g + h; }
	void SetF(double _f) { f = _f; }
	void SetParentRow(int _parentRow) { parentRow = _parentRow; }
	void SetParentCol(int _parentCol) { parentCol = _parentCol; }

	// used for set<cell>
	bool operator<(const Cell& other) const;

	// used for priority queue
	// return TRUE if this cell has higher priority (lower f, then lower g)
	bool operator>(const Cell& other) const;

	// compare position
	bool operator==(const Cell& other) const;
};

