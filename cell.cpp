#include "cell.h"
const State *Cell::getState() const
{
    return state;
}

void Cell::setState(const State *value)
{
    state = value;
}

Cell::Cell(int x, int y, const State *state)
{
    //TODO: init value; (t.kieu)
}

Cell::Cell(int x, int y)
{
    //TODO: init value; (t.kieu)
}

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{
    return y;
}
