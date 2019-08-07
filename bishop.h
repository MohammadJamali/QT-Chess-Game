#ifndef BISHOP_H
#define BISHOP_H

#include "chessman.h"

class Bishop : public Chessman
{
    public:
        Bishop(Point<int>ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short int id);

        virtual Matrix<int> getAvailablePlaces(Matrix<int> *map, bool = false);
};

#endif // BISHOP_H
