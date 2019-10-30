#ifndef INPUTMATRIXDATA_H
#define INPUTMATRIXDATA_H

#include <QWidget>
#include <QtWidgets>

#include <QGridLayout>
#include <QTableWidget>
#include <qpushbutton.h>
#include "Graph.h"
#include <QtSvg/QSvgWidget>
class InputMatrixData : public QWidget
{
    Q_OBJECT
private:
    QTableWidget *AdjacencyMatrix;
    QTableWidget *IncidenceMatrix;
    QPushButton  *AddNode;
    QPushButton  *DeleteNode;
    QComboBox    *ActiveNodes;
    QLabel       *Image;
    QPushButton  *createButton(const QString str);
    Graph MyGraph;
    void SetImage();
public:
    InputMatrixData(QWidget* pwgt = nullptr);
signals:

private slots:
    void slotAddNode();
};

#endif // INPUTMATRIXDATA_H
