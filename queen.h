#ifndef QUEEN_H
#define QUEEN_H

#include "chessman.h"

class Queen : public Chessman
{
    public:
        Queen(Point<int>ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short int id);

        virtual Matrix<int> getAvailablePlaces(Matrix<int> *map, bool = false);
};

#endif // QUEEN_H
