#ifndef CHESSMAN_H
#define CHESSMAN_H

#include "graphicitem.h"
#include "matrix.h"
#include "point.h"

#include <QGraphicsItem>
#include <QPainter>
#include <string>
#include <iostream>

#define IsBounded(x, y) ((x) >= 0 && (x) <= 7 && (y) >= 0 && (y) <= 7)

#define Taw         256
#define CheckMate  -1
#define CheckMater -256
#define Available   128
#define Block      -128
#define Enemy       64
#define Danger     -64
#define Castling(X) ((X) > 30 && (X) < 39)
#define TRCastling    32
#define TLCastling    33
#define BRCastling    34
#define BLCastling    35

using std::count;
using std::endl;

enum Groups {Black, White};

class Chessman : public QObject, public GraphicItem
{
        Q_OBJECT

    public:
        Chessman(Point<int> ChessMapLocation, int x, int y, int h, int w, string name, Groups group, unsigned short int id);

        void setGroup(Groups);
        Groups getGroup();

        void setID(unsigned short int);
        unsigned short int GetID() const;

        void setChessMapLocation(Point<int>ChessMapLocation);
        Point<int>GetChessMapLocation() const;

        void moveToNextPosition(int PosX, int PosY);

        void setDeleteState(bool);
        bool isDeleted();

        void incrementMoves();
        unsigned short int getMoveNumbers();

        virtual Matrix<int> getAvailablePlaces(Matrix<int> *map, bool JustDangers = false) = 0;

    signals:
        void onClicked(GraphicItem* graphicItem);

    protected:
        // virtual pure functions inherited from QGraphicsItem
        virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
        virtual void advance(int);

        virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    private:
        Point<int> location;
        Groups group;
        string imagePath;
        unsigned short int ID;
        unsigned short int moveNumber;
        int nextPosition[2];
        bool deleteState;
};

#endif // CHESSMAN_H
