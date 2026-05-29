#include "Cell.h"

Cell::Cell(): row(0), col(0), g(0.0), h(0.0), f(0.0), parentRow(-1), parentCol(-1) { }

Cell::Cell(int _row, int _col, double _g, double _h, int _parentRow, int _parentCol)
    : row(_row), col(_col), g(_g), h(_h), f(_g + _h), parentRow(_parentRow), parentCol(_parentCol) { }

bool Cell::operator<(const Cell& other) const
{
	if (row != other.row) return row < other.row;
	return col < other.col;
}

bool Cell::operator>(const Cell& other) const {
	if (f != other.f) return f > other.f;
	return g < other.g;
}

bool Cell::operator==(const Cell& other) const
{
	return row == other.row && col == other.col;
}
