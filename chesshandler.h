#ifndef ChessHandler_H
#define ChessHandler_H

#define IsBounded(x, y) ((x) >= 0 && (x) <= 7 && (y) >= 0 && (y) <= 7)

#include "pawn.h"
#include "rook.h"
#include "king.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "box.h"
#include "matrix.h"

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::stoi;
using std::to_string;

enum TawType
{
    WPawn = 0, WRook, WKnight, WBishop, WQueen, WKing,
    BPawn, BRook, BKnight, BBishop, BQueen, BKing
};

class ChessHandler : public QObject
{
        Q_OBJECT

    public:
        ChessHandler(QGraphicsScene& scene);

        void DrawChessmans();

        int DeleteChessmanPosX, DeleteChessmanPosY;

    private slots:
        void generateHighlightBoxes(GraphicItem* graphicItem = nullptr);
        void highlightBoxHandler(GraphicItem* graphicItem = nullptr);

    private:
        Groups turn;

        const char* ChessmanName(int Type);
        void clearHighlightBoxes();
        bool isCheckmated();
        void checkMate(bool isCheckmated);
        Matrix<int>* cleanupDanger(Matrix<int>* dangerMatrix, Chessman* king);
        Matrix<int>* mergDanger(Matrix<int>* dangerMatrix, Matrix<int> availablePlaces);

        vector<Box*> highlightBoxes;
        vector<Chessman*> chessmans;

        vector<Chessman*> blackChessmans;
        vector<Chessman*> whiteChessmans;
        Chessman* whiteKing;
        Chessman* blackKing;
        Chessman* selectedChessman;

        unsigned short int threats;
        Matrix<int>* threatMap;

        QGraphicsScene& Scene;

        Matrix<int> map;
};

#endif // ChessHandler_H
