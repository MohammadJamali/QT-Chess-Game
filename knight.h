#ifndef KNIGHT_H
#define KNIGHT_H

#include "chessman.h"

class Knight : public Chessman
{
    public:
        Knight(Point<int>ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short int id);

        virtual Matrix<int> getAvailablePlaces(Matrix<int> *map, bool = false);
};

#endif // KNIGHT_H
