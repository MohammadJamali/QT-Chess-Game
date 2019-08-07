#ifndef CHESSMAP_H
#define CHESSMAP_H

#include "graphicitem.h"
#include "box.h"

#include <QGraphicsScene>
#include <QPixmap>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Chessmap : public GraphicItem
{
    public:
        Chessmap(QGraphicsScene &scene, int x = 0, int y = 0, int w = 400, int h = 400);
        ~Chessmap();

        void DrawMap();
        void SetBackGround();
        void DeleteMap();

    protected:
        virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        virtual void advance(int);

        virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    private:
        vector<Box*> MapComponents;

        QGraphicsPixmapItem BackGround;

        QGraphicsScene &Scene;

};

#endif // CHESSMAP_H
