#ifndef INPUTMATRIXDATA_H
#define INPUTMATRIXDATA_H

#include <QWidget>
#include <QtWidgets>

#include <QGridLayout>
#include <QTableWidget>
#include <qpushbutton.h>
#include "Graph.h"
#include <QtSvg/QSvgWidget>
#include "WidgetShowImage.h"
class InputMatrixData : public QWidget
{
    Q_OBJECT
private:
    QTableWidget *AdjacencyMatrix;
    QTableWidget *IncidenceMatrix;
    QPushButton  *AddNode;
    QPushButton  *DeleteNode;
    QComboBox    *ActiveNodes;
    QPushButton  *createButton(const QString str);
    Graph MyGraph;
public:
    InputMatrixData(QWidget* pwgt = nullptr);
private slots:

};

#endif // INPUTMATRIXDATA_H
