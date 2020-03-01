#include "cell.h"
const State *Cell::getState() const
{
    return state;
}

void Cell::setState(const State *value)
{
    state = value;
}


// constructors
Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
}


Cell::Cell(int x, int y, const State* state){
    this->x = x;
    this->y = y;
    this->state = state;
}

// destructor
Cell::~Cell() {}

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{

    return y;
}