#include "neighbor_position.h"

/* Written by DuongHV */

NeighborPosition::NeighborPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

NeighborPosition::~NeighborPosition()
{

}

int NeighborPosition::getX() const
{
   return this->x;
}
int NeighborPosition::getY() const 
{
   return this->y;
}
