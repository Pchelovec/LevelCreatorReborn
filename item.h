#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include<QDebug>
#include <QPoint>
#include <QPixmap>

class Item
{
public:
    Item(){}
    Item(QPixmap pixmap,QPoint startPos){this->pixmap=pixmap;this->startPosition=startPos;}
    friend bool operator==(const Item& lhs, const Item& rhs){
        return (QString::compare(lhs.name,rhs.name)==0);
    }



    QPoint startPosition;
    QPixmap pixmap;
    QString name;
    QSize size;

    QSize getSize(){return size;}
};
#endif // ITEM_H
