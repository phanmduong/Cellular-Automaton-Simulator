#include "cell.h"

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
}

Cell::~Cell()
{

}

const State *Cell::getState() const
{
    return state;
}

void Cell::setState(const State *value)
{
    state = value;
}

Cell::Cell(int x, int y,const State* state){
    this->x = x;
    this->y = y;
    this->state = state;
}

int Cell::getX() const
{
    return x;
}

int Cell::getY() const
{

    return y;
}
