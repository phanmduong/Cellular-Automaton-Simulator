#ifndef CELL_H
#define CELL_H
#include "state.h"
class Cell
{
    int x,y;
    const State *state;

public:

    Cell(int x, int y, State const *state);
    Cell(int x, int y);

    ~Cell();

    int getX() const;
    int getY() const;

    const State *getState() const;
    void setState(const State *value);
};

#endif // CELL_H
