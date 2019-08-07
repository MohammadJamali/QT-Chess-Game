#include "chesshandler.h"
#include "matrix.h"

#include <QGraphicsItem>

ChessHandler::ChessHandler(QGraphicsScene& scene):
    Scene(scene),
    map(Matrix<int>(8, 8, 0))
{
    for(int i = 0; i < 8 ; i++)
    {
        map(1, i) = BPawn;
        map(6, i) = WPawn;
    }

    for(int i = 0; i < 2 ; i++)
    {
        map(0, i * 7) = BRook;
        map(7, i * 7) = WRook;
        map(0, 1 + (i * 5)) = BKnight;
        map(7, 1 + (i * 5)) = WKnight;
        map(0, 2 + (i * 3)) = BBishop;
        map(7, 2 + (i * 3)) = WBishop;
    }

    map(0, 3) = BQueen;
    map(7, 3) = WQueen;
    map(0, 4) = BKing;
    map(7, 4) = WKing;

    for(int i = 2; i < 6 ; i++)
        for(int j = 0 ; j < 8 ; j++)
            map(i, j) = Available;

    turn = White;
    threats = 0;
    threatMap = nullptr;
    selectedChessman = nullptr;
    DeleteChessmanPosX = 0;
    DeleteChessmanPosX = 400;
}

void ChessHandler::clearHighlightBoxes()
{
    for (unsigned int i = 0; i < highlightBoxes.size(); ++i)
        delete highlightBoxes[i];

    highlightBoxes.clear();
}

void ChessHandler::generateHighlightBoxes(GraphicItem* graphicItem)
{
    Box* box = static_cast<Box*>(graphicItem);
    int x = this->selectedChessman->GetPosY() / this->selectedChessman->GetHeight();
    int y = this->selectedChessman->GetPosX() / this->selectedChessman->GetWidth();
    int newX = box->GetPosY() / box->GetHeight();
    int newY = box->GetPosX() / box->GetWidth();
    // chenge chessman position on the map
    map.print();
    map(newX, newY) =  map(x, y);
    // last chess taw position is now Available
    map(x, y) = Available;
    // chessman must move to next position
    this->selectedChessman->incrementMoves();
    this->selectedChessman->setChessMapLocation(Point<int>(newY, newX));
    this->selectedChessman->moveToNextPosition(box->GetPosX(), box->GetPosY());

    if(box->GetObjName() == "Castling")
    {
        int tag = stoi(box->getTag());
        Point<int>* rookPosition;
        Point<int>* rookNewPosition;

        switch (tag)
        {
            case BLCastling:
                rookPosition = new Point<int>(0, 7);
                rookNewPosition = new Point<int>(3, 7);
                break;

            case TRCastling:
                rookPosition = new Point<int>(0, 0);
                rookNewPosition = new Point<int>(3, 0);
                break;

            case TLCastling:
                rookPosition = new Point<int>(7, 0);
                rookNewPosition = new Point<int>(5, 0);
                break;

            case BRCastling:
                rookPosition = new Point<int>(7, 7);
                rookNewPosition = new Point<int>(5, 7);
                break;

            default:
                throw std::bad_function_call();
        }

        Chessman* rook = nullptr;

        for (unsigned long counter = 0; counter < this->chessmans.size() && rook == nullptr; ++counter)
            if(this->chessmans[counter]->GetObjName() == "Rook" &&
               this->chessmans[counter]->GetChessMapLocation() == *rookPosition)
                rook = this->chessmans[counter];

        if(rook != nullptr)
        {
            map((*rookNewPosition).x(), (*rookNewPosition).y()) =  map((*rookPosition).x(), (*rookPosition).y());
            map((*rookPosition).x(), (*rookPosition).y()) = Available;
            rook->moveToNextPosition((*rookNewPosition).x() * rook->GetWidth(), (*rookNewPosition).y() * rook->GetHeight());
            rook->setChessMapLocation((*rookNewPosition));
        }

        delete rookNewPosition;
        delete rookPosition;
    }

    // check whether any chessmap should be deleted or not
    for (unsigned long counter = 0; counter < this->chessmans.size(); ++counter)
        if(this->chessmans[counter]->GetPosX() == box->GetPosX() &&
           this->chessmans[counter]->GetPosY() == box->GetPosY() &&
           turn != this->chessmans[counter]->getGroup())
        {
            this->chessmans[counter]->moveToNextPosition(DeleteChessmanPosX, DeleteChessmanPosY);
            this->chessmans[counter]->setDeleteState(true);
            DeleteChessmanPosY += this->chessmans[counter]->GetHeight();

            if(DeleteChessmanPosY == 400)
            {
                DeleteChessmanPosY = 0;
                DeleteChessmanPosX += this->chessmans[counter]->GetWidth();
            }
        }

    // turn must change to next group
    // all guide places must be cleared
    clearHighlightBoxes();
    // chage turn for next group
    turn = static_cast<Groups>((static_cast<int>(turn) + 1) % 2);
    checkMate(isCheckmated());
}

void ChessHandler::checkMate(bool isCheckmated)
{
}

bool ChessHandler::isCheckmated()
{
    unsigned short threats = 0;
    auto tempTreatMap = new Matrix<int>(8, 8, 0);
    Chessman* king;
    vector<Chessman*> enemies;

    if (turn == Black)
    {
        enemies = whiteChessmans;
        king = blackKing;
    }
    else if(turn == White)
    {
        enemies = blackChessmans;
        king = whiteKing;
    }

    foreach (auto chessman, enemies)
    {
        if(chessman->isDeleted())
            continue;

        auto availablePlaces = chessman->getAvailablePlaces(&map, false);
        auto kingLocationStatus =  availablePlaces(king->GetChessMapLocation().x(), king->GetChessMapLocation().y());

        if(kingLocationStatus == Enemy || kingLocationStatus == Available)
        {
            threats ++;
            tempTreatMap->operator()(chessman->GetChessMapLocation().x(), chessman->GetChessMapLocation().y()) = CheckMater;

            /*
             * Knight should not be consider becuase it does not threat other
             * chess beads with its line of sight, it should be consider separately
             */
            if(chessman->GetObjName() != "Knight")
            {
                tempTreatMap = mergDanger(tempTreatMap, availablePlaces);
            }
        }
    }

    if(threats > 0)
    {
        if(this->threatMap != nullptr)
            delete this->threatMap;

        tempTreatMap->print();
        this->threatMap = cleanupDanger(tempTreatMap, king);
        tempTreatMap->print();
    }

    this->threats = threats;
    return threats > 0;
}

Matrix<int>* ChessHandler::cleanupDanger(Matrix<int>* dangerMap, Chessman* king)
{
    int x = king->GetChessMapLocation().x();
    int y = king->GetChessMapLocation().y();

    for (int padding = 1; padding < 8 && IsBounded(x + padding, y) && dangerMap->operator()(x + padding, y) > 0; ++padding)
        if(dangerMap->operator()(x + padding, y) != CheckMater)
            dangerMap->operator()(x + padding, y) = CheckMate;

    for (int padding = 1; padding < 8 && IsBounded(x, y + padding) && dangerMap->operator()(x, y + padding)  > 0; ++padding)
        if(dangerMap->operator()(x, y + padding) != CheckMater)
            dangerMap->operator()(x, y + padding) = CheckMate;

    for (int padding = 1; padding < 8 && IsBounded(x + padding, y + padding) && dangerMap->operator()(x + padding, y + padding)  > 0; ++padding)
        if(dangerMap->operator()(x + padding, y + padding) != CheckMater)
            dangerMap->operator()(x + padding, y + padding) = CheckMate;

    for (int padding = 1; padding < 8 && IsBounded(x - padding, y) && dangerMap->operator()(x - padding, y)  > 0; ++padding)
        if(dangerMap->operator()(x - padding, y) != CheckMater)
            dangerMap->operator()(x - padding, y) = CheckMate;

    for (int padding = 1; padding < 8 && IsBounded(x, y - padding) && dangerMap->operator()(x, y - padding)  > 0; ++padding)
        if(dangerMap->operator()(x, y - padding) != CheckMater)
            dangerMap->operator()(x, y - padding) = CheckMate;

    for (int padding = 1; padding < 8 && IsBounded(x - padding, y - padding) && dangerMap->operator()(x - padding, y - padding)  > 0; ++padding)
        if(dangerMap->operator()(x - padding, y - padding) != CheckMater)
            dangerMap->operator()(x - padding, y - padding) = CheckMate;

    for (int padding = 1; padding < 8 && IsBounded(x - padding, y + padding) && dangerMap->operator()(x - padding, y + padding)  > 0; ++padding)
        if(dangerMap->operator()(x - padding, y + padding) != CheckMater)
            dangerMap->operator()(x - padding, y + padding) = CheckMate;

    for (int padding = 1; padding < 8 && IsBounded(x + padding, y - padding) && dangerMap->operator()(x + padding, y - padding)  > 0; ++padding)
        if(dangerMap->operator()(x + padding, y - padding) != CheckMater)
            dangerMap->operator()(x + padding, y - padding) = CheckMate;

    return dangerMap;
}

Matrix<int>* ChessHandler::mergDanger(Matrix<int>* dangerMatrix, Matrix<int> availablePlaces)
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (availablePlaces(i, j) == Available ||
                availablePlaces(i, j) == Enemy)
                dangerMatrix->operator()(i, j) += 1;

    return dangerMatrix;
}


void ChessHandler::highlightBoxHandler(GraphicItem* graphicItem)
{
    Chessman* chessman = static_cast<Chessman*>(graphicItem);

    if(chessman == nullptr)
    {
        printf("Chessman is nullptr, it can be cuased by unwanted memory cleanup.");
        return;
    }

    if(chessman->getGroup() != turn)
        return;

    if(selectedChessman != nullptr)
        this->selectedChessman->SetSelection(false);

    this->selectedChessman = chessman;
    // delete all guid boxes
    clearHighlightBoxes();
    // declare all next Available Places for this chessman
    auto availablePlace = chessman->getAvailablePlaces(&map, false);

    if(threats > 0)
    {
        if(chessman->GetObjName() == "King")
        {
            //            this->threatMap->print();
            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    if(this->threatMap->operator()(i, j) == 0)
                        continue;

                    if(this->threatMap->operator()(i, j) == CheckMater)
                        continue;

                    availablePlace(i, j) = Block;
                }
            }
        }
        else
        {
            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    if(this->threatMap->operator()(i, j) != CheckMate &&
                       this->threatMap->operator()(i, j) != CheckMater)
                    {
                        availablePlace(i, j) = Block;
                    }
                }
            }
        }
    }

    // draw all Available Places, which can be chosen by player
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Box* box = nullptr;

            if(availablePlace(i, j) == Available)
            {
                box = new Box(i * chessman->GetHeight(), j * chessman->GetHeight(), transparent_yellow, 50, "GuidPlace");
            }
            else if(availablePlace(i, j) == Enemy)
            {
                box = new Box(i * chessman->GetHeight(), j * chessman->GetHeight(), transparent_red, 50, "Enemy");
            }
            else if(Castling(availablePlace(i, j)))
            {
                box = new Box(i * chessman->GetHeight(), j * chessman->GetHeight(), transparent_green, 50, "Castling");
                box->setTag(to_string(availablePlace(i, j)));
            }

            if(box != nullptr)
            {
                QObject::connect(box, &Box::onClicked, this, &ChessHandler::generateHighlightBoxes);
                highlightBoxes.push_back(box);
                Scene.addItem(box);
            }
        }
    }
}

void ChessHandler::DrawChessmans()
{
    int chessmanSize = 50;
    unsigned short int counter = 0;

    for(unsigned short int i = 0 ; i < 8 ; i++)
    {
        for(unsigned short int j = 0 ; j < 8 ; j++)
        {
            if(Available != map(i, j))
            {
                Groups group = map(i, j) < 6 ? White : Black;
                Chessman* chessman = nullptr;

                switch (map(i, j))
                {
                    case BPawn:
                    case WPawn:
                        chessman = new Pawn(Point<int>(j, i), j * chessmanSize, i * chessmanSize, chessmanSize, chessmanSize, group, counter++);
                        break;

                    case BRook:
                    case WRook:
                        chessman = new Rook(Point<int>(j, i), j * chessmanSize, i * chessmanSize, chessmanSize, chessmanSize, group, counter++);
                        break;

                    case BKnight:
                    case WKnight:
                        chessman = new Knight(Point<int>(j, i), j * chessmanSize, i * chessmanSize, chessmanSize, chessmanSize, group, counter++);
                        break;

                    case BBishop:
                    case WBishop:
                        chessman = new Bishop(Point<int>(j, i), j * chessmanSize, i * chessmanSize, chessmanSize, chessmanSize, group, counter++);
                        break;

                    case BQueen:
                    case WQueen:
                        chessman = new Queen(Point<int>(j, i), j * chessmanSize, i * chessmanSize, chessmanSize, chessmanSize, group, counter++);
                        break;

                    case BKing:
                    case WKing:
                        chessman = new King(Point<int>(j, i), j * chessmanSize, i * chessmanSize, chessmanSize, chessmanSize, group, counter++);

                        if(group == Black)
                            blackKing = chessman;
                        else if(group == White)
                            whiteKing = chessman;

                        break;

                    default:
                        printf(":| what is this chessman ? i have never seen it until now ...");
                        break;
                }

                if(group == Black)
                    blackChessmans.push_back(chessman);
                else if(group == White)
                    whiteChessmans.push_back(chessman);

                QObject::connect(chessman, &Chessman::onClicked, this, &ChessHandler::highlightBoxHandler);
                this->chessmans.push_back(chessman);
                Scene.addItem(chessman);
            }
        }
    }
}
