#include "pawn.h"

Pawn::Pawn(Point<int> ChessMapLocation, int x, int y, int h, int w, Groups group, unsigned short id) : Chessman(ChessMapLocation, x, y, h, w, "Pawn", group, id)
{
}

Matrix<int> Pawn::getAvailablePlaces(Matrix<int>* map, bool JustDangers)
{
    Matrix<int> availablePlace = Matrix<int>(8, 8, Block);
    int x = GetChessMapLocation().x();
    int y = GetChessMapLocation().y();
    int direction = map->operator()(y, x) > 5 ? 1 : -1;
    int newCellGroup;

    if(!JustDangers)
    {
        if(getMoveNumbers() == 0)
        {
            if(map->operator()(y + direction, x) == Available)
            {
                availablePlace(x, y + direction) = Available;

                if(map->operator()(y + (2 * direction), x) == Available)
                {
                    availablePlace(x, y + (2 * direction)) = Available;
                }
            }
        }
        else if(IsBounded(y + direction, x))
        {
            if(map->operator()(y + direction, x) == Available)
            {
                availablePlace(x, y + direction) = Available;
            }
        }
    }

    if(IsBounded(y + direction, x + 1))
    {
        if(map->operator()(y + direction, x + 1) != Available)
        {
            newCellGroup = map->operator()(y + direction, x + 1) > 5 ? Black : White;

            if(this->getGroup() != newCellGroup )
            {
                availablePlace(x + 1, y + direction) = Enemy;
            }
        }
    }

    if(IsBounded(y + direction, x - 1))
    {
        if(map->operator()(y + direction, x - 1) != Available)
        {
            newCellGroup = map->operator()(y + direction, x - 1) > 5 ? Black : White;

            if(this->getGroup() != newCellGroup)
            {
                availablePlace(x - 1, y + direction) = Enemy;
            }
        }
    }

    return availablePlace;
}
