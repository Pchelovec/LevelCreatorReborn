#include "widget.h"
#include "ui_widget.h"

#include<QStandardItemModel>
#include<QDebug>
#include<QFileDialog>
#include<QTableWidgetItem>

#include<QPainter>
#include<QPixmap>
#include<QSize>
#include<QPoint>
#include<QLabel>
#include<QString>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"img"<<"X"<<"Y"<<"width"<<"height");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_plusPB_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}


void Widget::on_delPb_clicked()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    if(select->hasSelection() and select->selectedRows().size()>0){
        int delRow=select->selectedRows().first().row();
        qDebug()<<"Deleting"<<delRow;
        ui->tableWidget->removeRow(delRow);
    }
    else{
        qDebug()<<"select row for deleting";
    }
}

void Widget::on_tableWidget_itemSelectionChanged()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    if (select->hasSelection()){
        ui->delPb->setEnabled(true);
    }
    else{
        ui->delPb->setEnabled(false);
    }
}


void Widget::setBacgroundToTable(QString name)
{
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(name));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("0"));
}

QString Widget::getPath(QStringList l)
{
    QString result;
    for (int i=0;i<l.length()-1;i++){
        result+=l[i]+"/";
    }
    return result;
}

void Widget::draw()
{
//    //label for output
//    QLabel *label=new QLabel();

//    //extract drawed images
//    QPixmap *pixmap = getPixmap();

//    //set images to label and show
//    label->setPixmap(*pixmap);
//    label->show();
    ui->stackedWidget->setCurrentIndex(1);
    ui->contentLabel->setPixmap(*getPixmap());
}

QPixmap* Widget::getPixmap()
{
//    QSize size(400,600);

    Item bacground=getBackgroundFromFile();
    QList<Item> items=getElementsFromFile();
    qDebug()<<"we paint"<<bacground.name<<" and "<<items.length()<<" of elements";
    //draw
    PatchedGamePainter *gamePainter=new PatchedGamePainter(QSize(bacground.pixmap.width(),bacground.pixmap.height()));
    gamePainter->create();
    gamePainter->draw(0,0,bacground.pixmap);
    for (Item i:items){
        gamePainter->draw(i.startPosition.x(),i.startPosition.y(),i.pixmap.scaled(i.size.width(),i.size.height()));
    }
    return gamePainter->process();
}

Item Widget::getBackgroundFromFile()
{
    Item normalResult;

    QFile file( levelPath+"level.txt" );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QString back;
        QTextStream stream( &file );
        stream>>back;

        normalResult.name=levelPath+(back.split(" ")[0]);

        QPixmap pix;
        pix.load(normalResult.name);
        normalResult.pixmap=pix;

    }
    return normalResult;
}

QList<Item> Widget::getElementsFromFile()
{
    QList<Item> result;
    QFile file( levelPath+"level.txt" );
    if ( file.open(QIODevice::ReadWrite) )
    {

        QTextStream in(&file);
        in.readLine();//first line it is background read to nowhere
              while (!in.atEnd()) {
//                  process_line(line);

                  QString line = in.readLine();
                  qDebug()<<"line:"<<line;
                QTextStream stream( &file );
                qDebug()<<(line.split(" ")[0]);

                Item oneItem;
                oneItem.name=levelPath+(line.split(" ")[0]);

                QPixmap pix;
                pix.load(oneItem.name);
                oneItem.pixmap=pix;


                qDebug()<<"it was "<<oneItem.name;

                oneItem.startPosition=QPoint(line.split(" ")[1].toInt(),line.split(" ")[2].toInt());
                oneItem.size=QSize(line.split(" ")[3].toInt(),line.split(" ")[4].toInt());

                result.push_back(oneItem);
              }


    }
    file.close();
    qDebug()<<"we load"<<result.length()<<" elements";
    return result;
}


QList<Item> Widget::getElementsFromFileShort()
{
    QList<Item> result;
    QFile file( levelPath+"level.txt" );
    if ( file.open(QIODevice::ReadWrite) )
    {

        QTextStream in(&file);
        in.readLine();//first line it is background read to nowhere
              while (!in.atEnd()) {
//                  process_line(line);

                  QString line = in.readLine();
                  qDebug()<<"line:"<<line;
                QTextStream stream( &file );
                qDebug()<<(line.split(" ")[0]);

                Item oneItem;
                oneItem.name=(line.split(" ")[0]);

                QPixmap pix;
                pix.load(oneItem.name);
                oneItem.pixmap=pix;


                qDebug()<<"it was "<<oneItem.name;

                oneItem.startPosition=QPoint(line.split(" ")[1].toInt(),line.split(" ")[2].toInt());
                oneItem.size=QSize(line.split(" ")[3].toInt(),line.split(" ")[4].toInt());

                result.push_back(oneItem);
              }


    }
    file.close();
    qDebug()<<"we load"<<result.length()<<" elements";
    return result;
}

void Widget::on_pushButton_clicked()
{
    QString fileNamePath = QFileDialog::getOpenFileName(this,
          tr("Open Image"), "/home/", tr("Image Files (*.png *.jpg *.bmp *.webp *.txt)"));

    if (fileNamePath.split("/").last()=="level.txt"){
        levelPath=getPath(fileNamePath.split("/"));
        qDebug()<<"Load level from file"<<levelPath;
        Item background=getBackgroundFromFile();
        QList<Item> list=getElementsFromFileShort();

        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(list.length()+1);
        ui->tableWidget->setItem(0,0,new QTableWidgetItem(background.name));
        ui->tableWidget->setItem(0,1,new QTableWidgetItem("0"));
        ui->tableWidget->setItem(0,2,new QTableWidgetItem("0"));

        int row=0;
        for(Item i:list){
            row++;
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(i.name));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::number(i.startPosition.x())));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(i.startPosition.y())));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString::number(i.size.width())));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(QString::number(i.size.height())));
        }
    }
    else{
        qDebug()<<fileNamePath;

        QStringList list=fileNamePath.split("/");
        qDebug()<<list;
        qDebug()<<list.length()-1;
        QString fileName=fileNamePath.split("/")[list.length()-1];
        qDebug()<<fileName;

        setBacgroundToTable(fileName);
        levelPath=getPath(fileNamePath.split("/"));
        qDebug()<<"level path:"<<levelPath;
        //TODO level preload
    }
}


void Widget::on_saveToFilePB_clicked()
{
    QString resultFileName="level.txt";
    QString full=levelPath+resultFileName;
    QFile::remove(full);

    QFile file(full);
    QTextStream file_stream( &file );

    if (file.open(QIODevice::ReadWrite)){
        for (int i=0;i<ui->tableWidget->rowCount();i++){
            if (i==0){
                QString b_s(ui->tableWidget->item(i,0)->text()+" "+ui->tableWidget->item(i,1)->text()+" "+ui->tableWidget->item(i,2)->text());
                qDebug()<<b_s;
                file_stream<<b_s<<endl;
                continue;
            }
            QString i_s(ui->tableWidget->item(i,0)->text()+" "+ui->tableWidget->item(i,1)->text()+" "+ui->tableWidget->item(i,2)->text()+
                        " "+ui->tableWidget->item(i,3)->text()+" "+ui->tableWidget->item(i,4)->text());
            qDebug()<<i_s;
            file_stream<<i_s<<endl;
        }
    }
    file.close();


}

void Widget::on_prev_PB_clicked()
{
    draw();
}

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
