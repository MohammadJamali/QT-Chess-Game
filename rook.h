#ifndef ROOK_H
#define ROOK_H

#include "chessman.h"

class Rook : public Chessman
{
    public:
        Rook(Point<int>ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short int id);

        virtual Matrix<int> getAvailablePlaces(Matrix<int> *map, bool = false);
};

#endif // ROOK_H
