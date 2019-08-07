#include "rook.h"

Rook::Rook(Point<int>ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short id) : Chessman(ChessMapLocation, x, y, h, w, "Rook", group, id)
{
}

Matrix<int> Rook::getAvailablePlaces(Matrix<int>* map, bool)
{
    Matrix<int> availablePlace = Matrix<int>(8, 8, Block);
    int x = GetChessMapLocation().x();
    int y = GetChessMapLocation().y();

    for (int row = -1; row < 2; ++row)
    {
        for (int col = -1; col < 2; ++col)
        {
            if(row != col && row != (-col))
            {
                for (int counter = 1; counter < 8; ++counter)
                {
                    int sampledX = y + (col * counter);
                    int sampledY = x + (row * counter);

                    if(!IsBounded(sampledX, sampledY))
                        break;

                    if(map->operator()(sampledX, sampledY) == Available)
                        availablePlace(sampledY, sampledX) = Available;
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
    }

    return availablePlace;
}
