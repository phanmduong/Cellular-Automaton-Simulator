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

Cell* Grid::getCell(int x, int y)
{
    if(x<0 || x >= this->width) return nullptr;
    if(y<0 || y >= this->height) return nullptr;

    //else
    return this->cells[y*this->width+x];
}
