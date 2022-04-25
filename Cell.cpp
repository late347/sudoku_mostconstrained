#include "Cell.h"

Cell::Cell(int rowCoord, int colCoord, bool isClue, int val)
{
    theValue = val;
    rowIdx = rowCoord;
    colIdx = colCoord;
}

std::ostream& operator<<(std::ostream& os, const Cell& c)
{
    // best to print only the value and not the other data, to keep it clean
    // for board printing

    os << c.theValue;
    return os;
}