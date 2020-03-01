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
    Rule const *rule;

    // Get list neighbors of given cell
    vector<Cell*> getNeighbors(Cell const *cell);

public:
    // Constructor
    Grid(int width,int height, vector<NeighborPosition*> neigtborPositions, Rule const *rule);

    // Destructor
    ~Grid();

    // Get specific cell with given coordinates
    Cell* getCell(int x, int y);

    void generation();
};

#endif // GRID_H
