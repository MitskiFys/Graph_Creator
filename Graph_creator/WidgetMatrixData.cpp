#include "WidgetMatrixData.h"

InputMatrixData::InputMatrixData(QWidget *pwgt) : QWidget(pwgt)
{
    MyGraph.AddNode();
    MyGraph.AddHeader(1);
    QVBoxLayout* MainArea = new QVBoxLayout;
    //QGridLayout* MainArea = new QGridLayout;
    QGridLayout* ButtonArea = new QGridLayout();

    //Image area setup

    QGroupBox *imageGroup = new QGroupBox("Graph");
    QVBoxLayout *imageBox = new QVBoxLayout;

    QLabel *lbl = new QLabel;
    QPixmap pix("graph.svg");
    lbl->setPixmap(pix);

    imageBox->addWidget(lbl);
    imageBox->setAlignment(lbl,Qt::AlignCenter);
    imageGroup->setLayout(imageBox);
    imageGroup->setMinimumSize(320,240);

    //Button Area Setup

    QGroupBox *ButtonGroup = new QGroupBox("Functional");
    QGroupBox *deleteGroup = new QGroupBox("Choose node to delete");
    QVBoxLayout *deleteLay = new QVBoxLayout;
    QVBoxLayout *buttonLay = new QVBoxLayout;

    AddNode = new QPushButton("Add Node");
    AddNode->setMaximumSize(100, 40);
    ButtonArea->addWidget(AddNode, 0, 0);

    ActiveNodes = new QComboBox;
    ActiveNodes->addItems(MyGraph.Headers);
    ActiveNodes->setMaximumSize(100,40);
    deleteLay->addWidget(ActiveNodes);

    DeleteNode = new QPushButton("Delete Node");
    deleteLay->addWidget(DeleteNode);

    deleteGroup->setLayout(deleteLay);
    deleteLay->setAlignment(Qt::AlignHCenter);
    deleteLay->setAlignment(deleteLay, Qt::AlignHCenter);

    buttonLay->addWidget(AddNode);
    buttonLay->addWidget(deleteGroup);
    buttonLay->setSpacing(1);
    buttonLay->setAlignment(AddNode, Qt::AlignHCenter);
    ButtonGroup->setLayout(buttonLay);

    //Table setup

    QGroupBox *AdjacencyGroup = new QGroupBox("Adjacency Matrix");
    QGroupBox *IncidenceGroup = new QGroupBox("Incidence Matrix");
    QHBoxLayout *AdjacencyMatrixLay = new QHBoxLayout;
    QHBoxLayout *IncidenceMatrixLay = new QHBoxLayout;

    AdjacencyMatrix = new QTableWidget(1,1);
    AdjacencyMatrix->setMinimumSize(500,50);
    AdjacencyMatrix->setHorizontalHeaderLabels(MyGraph.Headers);

    AdjacencyMatrixLay->addWidget(AdjacencyMatrix);


    IncidenceMatrix = new QTableWidget(0,1);
    IncidenceMatrix->setMinimumSize(500,50);
    IncidenceMatrix->setHorizontalHeaderLabels(MyGraph.Headers);

    IncidenceMatrixLay->addWidget(IncidenceMatrix);

    AdjacencyGroup->setLayout(AdjacencyMatrixLay);
    IncidenceGroup->setLayout(IncidenceMatrixLay);

    //Functional Area setup

    QHBoxLayout *functionalArea = new QHBoxLayout;

    functionalArea->addWidget(AdjacencyGroup);
    functionalArea->addWidget(ButtonGroup);
    functionalArea->addWidget(IncidenceGroup);

    functionalArea->setAlignment(Qt::AlignCenter);

    //Layout setup

    MainArea->addWidget(imageGroup);
    MainArea->addItem(functionalArea);

    setLayout(MainArea);
}
