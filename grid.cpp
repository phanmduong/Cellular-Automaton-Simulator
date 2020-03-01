#include "grid.h"

/* Written by DuongHV */
Grid::Grid(int width,int height, vector<NeighborPosition*> neigtborPositions, Rule const *rule)
{
    this->width = width;
    this->height = height;
    this->neighborPositions = neighborPositions;
    this->rule = rule;
}

Grid::~Grid()
{

}

Cell Grid::getCell(int x, int y)
{
    for (unsigned int i=0; i<this->cells.size(); ++i)
    {
        Cell* cell = this->cells[i];
        if(true) // check x==cell->x and y == cell->y
            return *cell;
    }
}
