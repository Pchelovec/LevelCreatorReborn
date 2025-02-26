#include "patched_game_painter.h"

PatchedGamePainter::PatchedGamePainter(QSize baseScreenSize, QObject *parent) : QObject(parent)
{
    resultedPixmap=new QPixmap(baseScreenSize);
    resultedPixmap->fill(Qt::transparent);
}

PatchedGamePainter *PatchedGamePainter::create()
{
    painter=new QPainter(resultedPixmap);
    return this;
}

PatchedGamePainter *PatchedGamePainter::draw(int start_xPosition, int start_yPosition, const QPixmap obj)
{
    painter->drawPixmap(start_xPosition,start_yPosition,obj);
    return this;
}

QPixmap *PatchedGamePainter::process()
{
    painter->end();
    return resultedPixmap;
}
