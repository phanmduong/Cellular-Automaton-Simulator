#ifndef GRID_H
#define GRID_H
#include <cell.h>
#include <rule.h>
#include <neightbor_position.h>
#include <vector>

class Grid
{
    int width;
    int height;
    vector<Cell*> cells;
    vector<NeightborPosition*> neigtborPositions;
    Rule *rule;

    vector<Cell*> getNeighbors(Cell const *cell);

public:
    Grid(int width,int height, vector<NeightborPosition*> neigtborPositions, Rule const *Rule); // a.V-Duong

    Cell getCell(int x, int y); //a.V-Duong

    void generation();


};

#endif // GRID_H
