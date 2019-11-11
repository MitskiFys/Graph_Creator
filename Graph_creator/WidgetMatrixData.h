#ifndef INPUTMATRIXDATA_H
#define INPUTMATRIXDATA_H

#include <QWidget>
#include <QtWidgets>
#include <thread>
#include <QGridLayout>
#include <QTableWidget>
#include <qpushbutton.h>
#include "Graph.h"
#include <QtSvg/QSvgWidget>
#include "ImageCreator.h"
class InputMatrixData : public QWidget
{
    Q_OBJECT
private:
    QTableWidget *AdjacencyMatrix;
    QTableWidget *IncidenceMatrix;
    QPushButton  *AddNode;
    QPushButton  *DeleteNode;
    QPushButton  *AddEdge;
    QComboBox    *ActiveNodes;
    QLabel       *Image;
    QComboBox    *ShortestWayFrom;
    QComboBox    *ShortestWayTo;
    QLabel       *ShortestWayLen;
    QPushButton  *createButton(const QString str);
    Graph MyGraph;
    ImageCreator* imageCreator = new ImageCreator;
    void SetImage(int From = 0, int To = 0);
public:
    InputMatrixData(QWidget* pwgt = nullptr);
signals:

private slots:
    void slotSetImage();
    void slotAddNode();
    void slotAdjacencyCellUpdate();
    void slotDeleteNode();
    void slotUpdateIncMatrix();
    void slotShortWay();
    void slotAddEdge();
    void slotIncidenceCellUpdate();
};


#endif // INPUTMATRIXDATA_H
