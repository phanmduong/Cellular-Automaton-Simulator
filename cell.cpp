#include "cell.h"

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
}

Cell::Cell(int x, int y, State state){
    this->x = x;
    this->y = y;
    this->state = state;
}

State Cell::getState() const
{
    return state;
}

void Cell::setState(const State &value)
{
    state = value;
}
