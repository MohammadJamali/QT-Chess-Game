#include "knight.h"

Knight::Knight(Point<int> ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short id) : Chessman(ChessMapLocation, x, y, h, w, "Knight", group, id)
{
}

Matrix<int> Knight::getAvailablePlaces(Matrix<int>* map, bool)
{
    Matrix<int> availablePlace = Matrix<int>(8, 8, Block);
    int x = GetChessMapLocation().x();
    int y = GetChessMapLocation().y();
    int X = 0,
        Y = 0,
        newCellGroup;

    for(unsigned short int i = 0; i < 8 ; i++)
    {
        switch (i)
        {
            case 0:
                X = 1;
                Y = 2;
                break;

            case 1:
                X = 1;
                Y = -2;
                break;

            case 2:
                X = -1;
                Y = 2;
                break;

            case 3:
                X = -1;
                Y = -2;
                break;

            case 4:
                X = 2;
                Y = 1;
                break;

            case 5:
                X = 2;
                Y = -1;
                break;

            case 6:
                X = -2;
                Y = 1;
                break;

            case 7:
                X = -2;
                Y = -1;
                break;
        }

        if(IsBounded(x + X, y + Y))
        {
            newCellGroup = map->operator()(y + Y, x + X) > 5 ? Black : White;

            if(map->operator()(y + Y, x + X) != Available)
            {
                if(this->getGroup() != newCellGroup)
                {
                    availablePlace(x + X, y + Y) = Enemy;
                }
            }
            else
            {
                availablePlace(x + X, y + Y) = Available;
            }
        }
    }

    return availablePlace;
}
