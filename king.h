#ifndef KING_H
#define KING_H

#include "chessman.h"
#include "chesshandler.h"

class King : public Chessman
{
    public:
        King(Point<int>ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short int id);

        virtual Matrix<int> getAvailablePlaces(Matrix<int> *map, bool = false);
};

#endif // KING_H
