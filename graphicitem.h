#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsView>
#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::setw;

class GraphicItem : public QGraphicsItem
{
    public:
        GraphicItem(int x, int y, int h, int w, string name);

        void SetPosX(int);
        void SetPosY(int);
        void SetHeight(int);
        void SetWidth(int);
        void SetName(string);
        void SetValue(string);
        void SetSelection(bool state);  // set isSelected flag true, when it's selected

        int GetPosX()     const;        // get x position of graphical object
        int GetPosY()     const;        // get y position of graphical object
        int GetHeight()   const;        // get height of graphical object
        int GetWidth()    const;        // get width of graphical object
        bool GetSelection() const;      // return isSelected flag to someone who want to know
        string GetObjName() const;      // get name of graphical object
        string GetValue() const;

        string getTag() const;
        void setTag(const string &value);

    protected :
        // virtual pure functions inherited from QGraphicsItem
        virtual QRectF   boundingRect() const;// declate bounding recangle of object ( access place )
        virtual void     paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) = 0;
        virtual void     advance(int) = 0;       // calculate paint variable before rendering

        void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;

    private:
        int PosX, PosY,     // Position of top and left of the object
            Height, Width;  // Height and Width of the object

        string objName;     // name of the object
        string Value;       // defult or current object value like textbox text, colorbox color and ...

        string tag;
        bool Selection;
};

#endif // GRAPHICITEM_H
