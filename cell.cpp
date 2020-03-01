#include "cell.h"

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{
    return y;
}

Cell::Cell(int x, int y, State state)
{

}

State Cell::getState() const
{
    return state;
}

void Cell::setState(const State &value)
{
    state = value;
}
