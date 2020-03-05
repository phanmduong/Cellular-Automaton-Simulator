#include "grid.h"
#include <QDebug>

/* Written by DuongHV */

Grid::Grid(int width,int height, vector<NeighborPosition*> neigtborPositions, Rule *rule, vector<State *> states)
{
    this->width = width;
    this->height = height;
    this->neighborPositions = neigtborPositions;
    this->rule = rule;
    this->states = states;
    this->createGridCells();
}

Grid::~Grid()
{
    // Release all cells from grid
    this->cells.clear();
}

Cell* Grid::getCell(int x, int y)
{
    if (x<0 || x >= this->width) return nullptr;
    if (y<0 || y >= this->height) return nullptr;

    //else
    return this->cells[y*this->width+x];
}

// Get specific cell with given coordinates from specific matrix
Cell* Grid::getCellFromMatrix(int x, int y, vector<Cell> *vtCells)
{
    if (x<0 || x >= this->width) return nullptr;
    if (y<0 || y >= this->height) return nullptr;

    //else
    return &(*vtCells)[y*this->width+x];
}

/* Generate all new state of each cell in grid at each generation and update for all cells */
void Grid::generation()
{
    vector<Cell> cells;
    for (unsigned i = 0; i < this->cells.size(); i++)
    {
        Cell cell(this->cells[i]);
        cells.push_back(cell);
    }

    for (unsigned i = 0; i < cells.size(); i++)
    {
        vector<Cell*> neighbors = this->getNeighbors(&cells[i], &cells);
        State *state;
        try {
            state = this->rule->excuteRule(&cells[i], neighbors, this->states);
        } catch(...)
        {
            emit this->rule_error("Rule run error");

            return;
        }

        if (state == nullptr){
            qDebug() << "Not found state";
            emit this->rule_error("Not found state");
            return;
        }


        this->cells[i]->setState(state);
    }
}

/* Get list neighbor cells from given cell */
int Grid::getWidth() const
{
    return width;
}

int Grid::getHeight() const
{
    return height;
}

vector<State *> Grid::getStates() const
{
    return states;
}

vector<Cell*> Grid::getNeighbors(const Cell *cell, vector<Cell> *cells)
{
    vector<Cell*> listNeighbors;

    for (unsigned i = 0; i < this->neighborPositions.size(); i++)
    {
        int x_neighbor = this->calculateCoordinates(cell->getX(), this->neighborPositions[i]->getX(), this->width);
        int y_neighbor = this->calculateCoordinates(cell->getY(), this->neighborPositions[i]->getY(), this->height);
        Cell* tmp = getCellFromMatrix(x_neighbor,y_neighbor,cells);
        listNeighbors.push_back(tmp);
    }

    return listNeighbors;
}

/* 
In order to calculate coordinate of neighbor cell, we need to do step by step as below
(with assumption: value of coordinate is always >= 0)

Step 1: Add the coordinates of the specified cell to the relative position of the neighboring cell
Step 2: Get the result after step 1 to bring the mod to the corresponding length (width/height) of the grid
Step 3: Consider the sign of the result in step 2:
    + If result> = 0: keep the value
    + if result <0: final value = result of step 2 + the corresponding length (width/height) of the grid
*/
int Grid::calculateCoordinates(int idx_cell, int distance, int length)
{
    int coordinate = (idx_cell+distance)%length;

    if (coordinate < 0)
    {
        coordinate += length;
    }

    return coordinate;
}

/* Initialize all cells of grid without state value */
void Grid::createGridCells()
{
    for (unsigned j = 0; j < this->height; j++){
        for (unsigned i = 0; i < this->width; i++){
                Cell* cell = new Cell(i,j);
                this->cells.push_back(cell);
        }
    }
}




