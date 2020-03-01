#include "grid.h"

/* Written by DuongHV */
Grid::Grid(int width,int height, vector<NeighborPosition*> neigtborPositions, Rule const *rule)
{
    this->width = width;
    this->height = height;
    this->neighborPositions = neigtborPositions;
    this->rule = rule;
    this->createGridCells();
}

Grid::~Grid()
{
    //TODO: delete cells (v.duong)
}

Cell* Grid::getCell(int x, int y)
{
    if(x<0 || x >= this->width) return nullptr;
    if(y<0 || y >= this->height) return nullptr;

    //else
    return this->cells[y*this->width+x];
}

void Grid::generation()
{
    //TODO: foreach cell (v.duong)
   {
        vector<Cell*> neighbors = this->getNeighbors(cell);
        this->rule->excuteRule(cell, neighbors);
    }
}

vector<Cell*> Grid::getNeighbors(const Cell *cell)
{
    //TODO: get neigbors of cell (v.duong)
}

void Grid::createGridCells()
{
    // TODO: create cells with each x, y don't have state (v.duong)
}
