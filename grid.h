#ifndef GRID_H
#define GRID_H
#include <cell.h>
#include <rule.h>
#include <neighbor_position.h>
#include <vector>

class Grid
{
    int width;
    int height;
    vector<Cell*> cells;
    vector<NeighborPosition*> neighborPositions;
    Rule *rule;

    vector<Cell*> getNeighbors(Cell const *cell);

public:
    Grid(int width,int height, vector<NeighborPosition*> neigtborPositions, Rule const *Rule); // a.V-Duong

    Cell getCell(int x, int y); //a.V-Duong

    void generation();


};

#endif // GRID_H
