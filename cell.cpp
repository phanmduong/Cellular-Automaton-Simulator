#include "cell.h"


// constructors
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

// destructor
Cell::~Cell() {}

State Cell::getState() const
{
    return state;
}

void Cell::setState(const State &value)
{
    this->state = value;
}
