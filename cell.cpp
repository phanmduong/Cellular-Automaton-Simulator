#include "cell.h"

Cell::Cell()
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
