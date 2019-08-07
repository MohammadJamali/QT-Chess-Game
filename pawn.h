#ifndef PAWN_H
#define PAWN_H

#include "chessman.h"

class Pawn : public Chessman
{
    public:
        Pawn(Point<int>ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short int id);

        virtual Matrix<int> getAvailablePlaces(Matrix<int> *map, bool = false);
};

#endif // PAWN_H
