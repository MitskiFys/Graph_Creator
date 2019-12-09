#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <graphviz/gvc.h>
#include <Graph.h>
#include <WidgetMatrixData.h>
#include <QtSvg/QGraphicsSvgItem>
#include "MyScene.h"
using namespace std;




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InputMatrixData MyWindow;

//    MyScene scene;
//    QGraphicsView view(&scene);
//    scene.setSceneRect(0, 0, 580, 580);

//    QObject::connect(&scene, SIGNAL(addNode()), &MyWindow, SLOT(slotAddNode()));
//    QObject::connect(&scene, SIGNAL(addNode()), &MyWindow, SLOT(slotUpdateIncMatrix()));
//    QObject::connect(&scene, SIGNAL(addNode()), &MyWindow, SLOT(slotUpdateAdjMatrix()));
//    QObject::connect(&scene, SIGNAL(addNode()), &MyWindow, SLOT(slotShortWay()));
   // QObject::connect(scene, SIGNAL(addNode()), MyWindow, SLOT(AddNode()));

    //view.show();
    MyWindow.show();

//    WidgetShowImage image;
//    image.show();
//    QWidget wgt;
//    QGraphicsScene scene(QRectF(-300,-10, 720, 240));

//    MyView* pView = new MyView(&scene);
//    QPushButton* ZoomIn = new QPushButton("&Zoom IN");
//    QPushButton* ZoomOut = new QPushButton("&Zoom OUT");

//    pView->setRenderHint(QPainter::Antialiasing, true);

//    QGraphicsPixmapItem* pPixmapItem = scene.addPixmap(QPixmap("graph.svg"));
//    pPixmapItem->setFlags(QGraphicsItem::ItemIsMovable);
//    //scene.clear();

//    QObject::connect(ZoomIn, SIGNAL(clicked()), pView, SLOT(slotZoomIn()));
//    QObject::connect(ZoomOut, SIGNAL(clicked()), pView, SLOT(slotZoomOut()));

//    QVBoxLayout* pvbxLayout = new QVBoxLayout;
//    pvbxLayout->addWidget(pView);
//    pvbxLayout->addWidget(ZoomIn);
//    pvbxLayout->addWidget(ZoomOut);

//    wgt.setLayout(pvbxLayout);
//    wgt.show();
    return a.exec();
}



