#ifndef NEIGHBOR_H
#define NEIGHBOR_H

/* Written by DuongHV */

class NeighborPosition
{
    int x, y;
public:
    // Constructor
    NeighborPosition(int x, int y);

    // Destructor
    ~NeighborPosition();

    // Getters
    int getX() const;
    int getY() const;
};

#endif // NEIGHBOR_H
