#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTableWidgetItem>
#include"patched_game_painter.h"
#include"item.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:

    void on_plusPB_clicked();
    void on_delPb_clicked();
    void on_tableWidget_itemSelectionChanged();
    void on_pushButton_clicked();
    void on_saveToFilePB_clicked();
    void on_prev_PB_clicked();

private:
    Ui::Widget *ui;
    QString levelPath;
    void setBacgroundToTable(QString name);
    QString getPath(QStringList l);
    void draw();
    QPixmap *getPixmap();
    Item getBackgroundFromFile();
    QList<Item> getElementsFromFile();
    QList<Item> getElementsFromFileShort();
};

#endif // WIDGET_H
