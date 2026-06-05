#include "Cell.h"

/***************************************************************************
Bachelor of Software Engineering
Media Design School
Auckland, New Zealand
(c) Year 1 Media Design School

Author                  : Sokveasna Mao
Email                   : maosokveasna48@gmail.com
Component code and name : GD1P02 - Algorithms and Data Structures
Name                    : Assessment 2

File                    : Cell.cpp

Description:
    Implements the Cell class used in the A* pathfinding algorithm.
    Contains constructors and operator overloads used for:
    - Open list (priority queue)
    - Closed list (set)
    - Path reconstruction
***************************************************************************/

/*==================Default Constructor========================*/
/*
    Initializes a Cell with default values:
    - Position set to (0,0)
    - Costs set to 0
    - Parent set to (-1,-1)
*/
Cell::Cell(): row(0), col(0), g(0.0), h(0.0), f(0.0),
    parentRow(-1), parentCol(-1) { }


/*==================Parameter Constructor========================*/
/*
	Initializes a Cell with specified values for position, costs, and parent.
*/
Cell::Cell(int _row, int _col, double _g, double _h, int _parentRow, int _parentCol)
    : row(_row), col(_col), g(_g), h(_h), f(_g + _h),
    parentRow(_parentRow), parentCol(_parentCol) { }

/*==================Operator <========================*/
bool Cell::operator<(const Cell& other) const
{

    if (row != other.row) return row < other.row;
    return col < other.col;
}

/*==================Operator >========================*/
bool Cell::operator>(const Cell& other) const
{
    if (f != other.f) return f > other.f;
    return g < other.g;
}

/*==================Operator == ========================*/
bool Cell::operator==(const Cell& other) const
{
    return row == other.row && col == other.col;
}