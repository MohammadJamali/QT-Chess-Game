#ifndef BOX_H
#define BOX_H

#define transparent_yellow  QColor(255,225,0,64)        // transparent yellow color
#define transparent_red     QColor(255,0,0,64)          // transparent red color
#define transparent_green   QColor(0,255,0,64)          // transparent green color
#define solid_dark_brown    QColor(233,186,129,225)     // dark brown color
#define solid_light_brown   QColor(158,91,64,225)       // light brown color

#include <QGraphicsItem>
#include <QPainter>
#include "graphicitem.h"

class Box :  public QObject, public GraphicItem
{
    Q_OBJECT

    public:
        Box(int x, int y, QColor objQColor, int Size, string name);

    protected:
        // overloaded pure funcion of QGraphicsItem class                             // return bounding Rectangle of object
        virtual void  paint(QPainter* ,const QStyleOptionGraphicsItem*, QWidget*);  // paiting object on the view port
        virtual void  advance(int);

        virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    signals:
       void onClicked(GraphicItem *graphicItem);

    private:
        QColor color;    // color of box
};

#endif // BOX_H
