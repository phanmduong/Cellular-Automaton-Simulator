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
    vector<State *> states; // list states
    Rule *rule;

    // Get list neighbor cells of given cell
    vector<Cell*> getNeighbors(Cell const *cell);

    /* Initialize all cells of grid without state value */
    void createGridCells();

    //In order to calculate coordinate of neighbor cell, we need to do step by step as below
    int calculateCoordinates(int idx_cell, int distance, int length);

public:
    // Constructor
    Grid(int width,int height, vector<NeighborPosition*> neigtborPositions, Rule *rule, vector<State *> states);

    // Destructor
    ~Grid();

    // Get specific cell with given coordinates
    Cell* getCell(int x, int y);

    // Generate all new state of each cell in grid at each generation and update for all cells
    void generation();
};

#endif // GRID_H
