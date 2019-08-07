#include "graphicitem.h"

GraphicItem::GraphicItem(int x, int y, int h, int w, string name)
{
    SetPosX(x);
    SetPosY(y);
    SetHeight(h);
    SetWidth(w);
    SetName(name);
    SetSelection(false);

    cout << ":-$ GraphicItem " << GetObjName() << " created on [" << x << ", " << y << "] : "
            << h << "X" << w << endl;
}

QRectF GraphicItem::boundingRect() const
{
    return QRectF( GetPosX(), GetPosY(), GetWidth(), GetHeight());
}

string GraphicItem::getTag() const
{
    return tag;
}

void GraphicItem::setTag(const string &value)
{
    tag = value;
}

void GraphicItem::SetValue(string input)
{
    Value = input;
}

void GraphicItem::SetSelection(bool input)
{
    cout << ":-$ GraphicItem (" << GraphicItem::GetObjName() << ") selected right now ." << endl;
    Selection = input;
}

bool GraphicItem::GetSelection() const
{
    return Selection;
}

void GraphicItem::SetPosX(int x)
{
    PosX = x; // set x position
}

void GraphicItem::SetPosY(int y)
{
    PosY = y;  // set y position
}

void GraphicItem::SetHeight(int h)
{
    Height = h > 0 ? h : 0; // set height size
}

void GraphicItem::SetWidth(int w)
{
    Width = w > 0 ? w : 0; // set width size
}

void GraphicItem::SetName(string n)
{
    objName = n; // set name of object
}

int GraphicItem::GetPosX() const
{
    return PosX; // get x position
}

int GraphicItem::GetPosY() const
{
    return PosY; // get y position
}
int GraphicItem::GetHeight() const
{
    return Height; // get height size
}
int GraphicItem::GetWidth() const
{
    return Width; // get width size
}

string GraphicItem::GetObjName() const
{
    return objName; // get name of object
}

string GraphicItem::GetValue() const
{
    return Value;
}
