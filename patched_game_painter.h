#ifndef PATCHEDGAMEPAINTER_H
#define PATCHEDGAMEPAINTER_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
class PatchedGamePainter : public QObject
{
    Q_OBJECT
public:
    explicit PatchedGamePainter(QSize baseScreenSize, QObject *parent = nullptr);
    PatchedGamePainter* create();
    PatchedGamePainter* draw(int start_xPosition, int start_yPosition,const QPixmap obj);
    QPixmap*process();

private:
    QPixmap *resultedPixmap;
    QPainter *painter;
};

#endif // PATCHEDGAMEPAINTER_H
