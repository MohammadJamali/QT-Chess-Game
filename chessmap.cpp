#include "chessmap.h"

Chessmap::Chessmap(QGraphicsScene &scene, int x, int y, int w , int h) :
    GraphicItem(x, y, w, h, "Chessmap"), Scene(scene) { }

Chessmap::~Chessmap()
{
    DeleteMap();
}

void Chessmap::DrawMap()
{
    int x = GraphicItem::GetPosX(), y = GraphicItem::GetPosY(), order=0,
            counter = 0, SizeOfBox = static_cast<int>(GraphicItem::GetHeight() / 8);

    // Drawing Chess Map
    for(int i=0; i<8 ; i++)
    {
        for(int j=0; j<4 ; j++)
        {
            MapComponents.push_back(new Box(x, y, order % 2 ? solid_dark_brown : solid_light_brown
                                                              , SizeOfBox, "MapBox"));
            Scene.addItem(MapComponents[counter++]);

            MapComponents.push_back(new Box(x + SizeOfBox, y,
                                            order % 2 ? solid_light_brown : solid_dark_brown,
                                            SizeOfBox, "MapBox"));

            Scene.addItem(MapComponents[counter++]);

            x+= (SizeOfBox * 2);
        }
        order++;
        y += SizeOfBox;
        x = GraphicItem::GetPosX();
    }
}

void Chessmap::DeleteMap()
{
    for (unsigned int counter = 0; counter < MapComponents.size(); ++counter)
       delete MapComponents.at(counter);
}

void Chessmap::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *){}

void Chessmap::advance(int){}

void Chessmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void Chessmap::SetBackGround()
{
    BackGround.setPixmap(QPixmap(":/Pic/BackGround.png"));
    BackGround.setPos((qreal)-20, (qreal)-25);
    Scene.addItem(&BackGround);
}
