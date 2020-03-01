#include "cell.h"

Cell::Cell()
{

}

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{
    return y;
}

State Cell::getState() const
{
    return state;
}

void Cell::setState(const State &value)
{
    state = value;
}
