#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

#include "chessmap.h"
#include "chesshandler.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    QApplication chess(argc, argv);                                 // Start of every Qt GUI application
    cout << "Welcome to BASU Chessman" << endl;
    QGraphicsScene Scene;                                           // create a GraphicsScene for creating a place for QGraphicsView
    Scene.setItemIndexMethod(QGraphicsScene::NoIndex);              // create every thing but don't index them ...
    Scene.setSceneRect(-20, -25, 850, 450);                         // setup the veiw-port location and window size
    QGraphicsView View(&Scene);                                     // create a white place for graphical objects
    View.setBackgroundRole(QPalette::QPalette::NoRole);
    View.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  // declare how to render new frame in view-port
    View.setRenderHint(QPainter::Qt4CompatiblePainting);            // declare rendering way
    View.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView,            // set graphical window title
                                          "2D Chess - Final Advanced Programming Project"));
    View.setMouseTracking(true);                                    // now on, i can traking mouse hover and click
    View.setFixedSize(852, 452);
    QTimer timer;                                                   // in this part we want to declare a timer for rendering
    QObject::connect(&timer, SIGNAL(timeout()), &Scene,
                     SLOT(advance()));                              // on each timeout , 'advance' function will be called
    timer.start(1000 / 60);                                         // 60 frames per second
    Chessmap objChessmap(Scene);
    objChessmap.SetBackGround();
    objChessmap.DrawMap();
    ChessHandler objChessHandler(Scene);
    objChessHandler.DrawChessmans();
    QImage image("://Pic//BKnight.png");
    QGraphicsPixmapItem item(QPixmap::fromImage(image));
    View.show();
    return chess.exec();
}
