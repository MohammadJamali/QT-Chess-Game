#include "king.h"

King::King(Point<int> ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short id) : Chessman(ChessMapLocation, x, y, h, w, "King", group, id)
{
}

Matrix<int> King::getAvailablePlaces(Matrix<int> *map, bool)
{
    Matrix<int> availablePlace = Matrix<int>(8, 8, Block);
    int x = GetChessMapLocation().x();
    int y = GetChessMapLocation().y();

    for (int row = -1; row < 2; ++row)
    {
        for (int col = -1; col < 2; ++col)
        {
            for (int counter = 1; counter < 2; ++counter)
            {
                int sampledX = y + (col * counter);
                int sampledY = x + (row * counter);

                if(!IsBounded(sampledX, sampledY ))
                    break;

                if(map->operator()(sampledX, sampledY) == Available)
                {
                    availablePlace(sampledY, sampledX) = Available;
                }
                else if(this->getGroup() != (map->operator()(sampledX, sampledY) > 5 ? Black : White))
                {
                    availablePlace(sampledY, sampledX) = Enemy;
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }

    if(getMoveNumbers() == 0)
    {
        bool emptyPath = true;

        // check for left rook-king
        for (int i = -3; i < 0 && emptyPath; i++)
            if(map->operator()(y, x + i) != Available)
                emptyPath = false;

        if(emptyPath)
        {
            if(this->getGroup() == Black && map->operator()(y, x - 4) == BRook)
            {
                availablePlace(x - 2, y) = TLCastling;
            }
            else if(this->getGroup() == White && map->operator()(y, x - 4) == WRook)
            {
                availablePlace(x - 2, y) = BLCastling;
            }
        }

        // check for right rook-king
        emptyPath = true;

        for (int i = 1; i < 3 && emptyPath; i++)
            if(map->operator()(y, x + i) != Available)
                emptyPath = false;

        if(emptyPath)
        {
            if(this->getGroup() == Black && map->operator()(y, x + 3) == BRook)
            {
                availablePlace(x + 2, y) = TLCastling;
            }
            else if(this->getGroup() == White && map->operator()(y, x + 3) == WRook)
            {
                availablePlace(x + 2, y) = BRCastling;
            }
        }
    }

    return availablePlace;
}
