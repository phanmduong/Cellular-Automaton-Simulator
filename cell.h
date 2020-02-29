#ifndef CELL_H
#define CELL_H
#include <state.h>

class Cell
{
    int x,y;
    State state;

public:
    Cell(int x, int y, State state);
    Cell(int x, int y);

    State getState() const; //kieu
    void setState(const State &value); //Kieu
};

#endif // CELL_H
