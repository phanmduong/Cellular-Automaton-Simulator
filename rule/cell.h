#ifndef CELL_H
#define CELL_H
#include "state.h"

using namespace std;

class Cell{
private: 
    State* state;
    int x;
    int y;
public:
    Cell(int x, int y, State *state);
    ~Cell();
    State getState();
    void setState(State *state);
};

#endif 
