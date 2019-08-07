#include "chessman.h"

Chessman::Chessman(Point<int> ChessMapLocation, int x, int y, int h, int w, string name, Groups group, unsigned short id)
    : GraphicItem(x, y, h, w, name), location(ChessMapLocation)
{
    setGroup(group);
    setID(id);
    setDeleteState(false);
    nextPosition[0] = nextPosition[1] = -1;
    moveNumber = 0;

    if(group == Black)
        imagePath = "://Pic//B";
    else
        imagePath = "://Pic//W";

    imagePath += name + ".png";
    this->setCursor(QCursor(Qt::PointingHandCursor));
    this->setZValue(2.0);
}

void Chessman::setID(unsigned short int input)
{
    ID = input;
}

unsigned short int Chessman::GetID() const
{
    return ID;
}

void Chessman::setGroup(Groups input)
{
    group = input;
}

Groups Chessman::getGroup()
{
    return group;
}

void Chessman::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawImage(GetPosX(), GetPosY(), QImage(imagePath.c_str()));
}

void Chessman::setChessMapLocation(Point<int>ChessMapLocation)
{
    this->location = ChessMapLocation;
}

Point<int>Chessman::GetChessMapLocation() const
{
    return this->location;
}

void Chessman::moveToNextPosition(int PosX, int PosY)
{
    nextPosition[0] = PosX;
    nextPosition[1] = PosY;
}

void Chessman::advance(int step)
{
    if(!step) return;

    if(nextPosition[0] != -1 || nextPosition[1] != -1)
    {
        int Xdistance = nextPosition[0] - GetPosX(); // declare distance bitween two point
        int Ydistance = nextPosition[1] - GetPosY(); // declare distance bitween two point

        if(GetPosX() != nextPosition[0] && Xdistance > 1)
            SetPosX(GetPosX() + 3);     // set new x point
        else if(Xdistance < -3)
            SetPosX(GetPosX() - 3);     // set new -x point
        else
            SetPosX(nextPosition[0]);  // fix new position to its actual location

        if(GetPosY() != nextPosition[1] && Ydistance > 1)
            SetPosY(GetPosY() + 3);     // set new y position
        else if(Ydistance < -3)
            SetPosY(GetPosY() - 3);     // set new -y position
        else
            SetPosY(nextPosition[1]);  // fix new position to its actual location

        setPos((qreal)GetPosX() / 500, (qreal)GetPosY() / 500);

        if(GetPosY() == nextPosition[1] && GetPosX() == nextPosition[0])
        {
            moveNumber++;
            nextPosition[0] = nextPosition[1] = -1; // deselect next position
        }
    }
}

void Chessman::setDeleteState(bool input)
{
    deleteState = input;
}

bool Chessman::isDeleted()
{
    return deleteState;
}

void Chessman::incrementMoves()
{
    moveNumber++;
}

unsigned short int Chessman::getMoveNumbers()
{
    return moveNumber;
}

void Chessman::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(isDeleted()) return;

    onClicked(this);
    QGraphicsItem::mousePressEvent(event);
}

