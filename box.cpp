#include "box.h"

Box::Box(int x, int y, QColor objQColor, int Size, string name):
    GraphicItem(x, y, Size, Size, name)
{
    color  = objQColor;
}

void Box::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // paiting box with its x, y poses and h, w sizes and special color
    painter->fillRect(GetPosX(), GetPosY(),  GetHeight(), GetWidth(), color);
}

void Box::advance(int) {}

void Box::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // this GraphicItem selected ,set selection flag true
    SetSelection(true);
    onClicked(this);
    //    QGraphicsItem::mousePressEvent(event);
}
