#ifndef CELL_H
#define CELL_H
#include <state.h>

class Cell
{
    int x,y;
    State state;

public:
    Cell(int x, int y, State state); //kieu
    Cell(int x, int y); //Kieu

    State getState() const;
    void setState(const State &value);
    int getX() const;
    int getY() const;
};

#endif // CELL_H
