#include "WidgetMatrixData.h"

InputMatrixData::InputMatrixData(QWidget *pwgt) : QWidget(pwgt)
{
    MyGraph.AddNode();
    MyGraph.AddHeader(1);
    QHBoxLayout* UpArea = new QHBoxLayout;
    QVBoxLayout* MainArea = new QVBoxLayout;
    connect(imageCreator, SIGNAL(ImageCreated()), SLOT(slotSetImage()));
    //Image area setup

    QGroupBox *imageGroup = new QGroupBox("Graph");
    QGroupBox *shortestWayGroup = new QGroupBox("ShortestWay");
    QHBoxLayout *imageBox = new QHBoxLayout;
    QHBoxLayout *NodsForShWay = new QHBoxLayout;
    QHBoxLayout *Result = new QHBoxLayout;
    QVBoxLayout *ShortestWay = new QVBoxLayout;
    QHBoxLayout *LayWithImageAndShortestWay = new QHBoxLayout;


    ShortestWayTo = new QComboBox;
    ShortestWayTo->addItems(MyGraph.NodeHeaders);
    ShortestWayTo->setMaximumSize(60,40);
    ShortestWayFrom = new QComboBox;
    ShortestWayFrom->addItems(MyGraph.NodeHeaders);
    ShortestWayFrom->setMaximumSize(60,40);
    ShortestWayLen = new QLabel;
    QLabel *from = new QLabel("From ");
    QLabel *to = new QLabel(" to ");
    to->setAlignment(Qt::AlignCenter);
    to->setMaximumWidth(60);
    from->setAlignment(Qt::AlignCenter);
    from->setMaximumWidth(60);
    QLabel *Length = new QLabel("Length = ");

    NodsForShWay->addWidget(from);
    NodsForShWay->addWidget(ShortestWayFrom);
    NodsForShWay->addWidget(to);
    NodsForShWay->addWidget(ShortestWayTo);
    QSpacerItem* spase = new QSpacerItem(40,10);
    Result->addItem(spase);
    Result->addWidget(Length);
    Result->addWidget(ShortestWayLen);

    ShortestWay->addItem(NodsForShWay);
    ShortestWay->addItem(Result);
    ShortestWay->setAlignment(NodsForShWay ,Qt::AlignCenter);

    shortestWayGroup->setLayout(ShortestWay);
    shortestWayGroup->setMinimumSize(320,120);
    shortestWayGroup->setMaximumSize(320,120);

    Image = new QLabel;

    imageBox->addWidget(Image);
    imageBox->setAlignment(Image,Qt::AlignCenter);
    imageGroup->setLayout(imageBox);
    imageGroup->setMinimumSize(320,320);
    LayWithImageAndShortestWay->addWidget(imageGroup);

    //Button Area Setup

    QGroupBox *ButtonGroup = new QGroupBox("Functional");
    QGroupBox *deleteGroup = new QGroupBox("Choose node to delete");
    QVBoxLayout *deleteLay = new QVBoxLayout;
    QVBoxLayout *buttonLay = new QVBoxLayout;



    AddEdge = new QPushButton("Add Edge");
    AddEdge->setMaximumSize(100,40);

    AddNode = new QPushButton("Add Node");
    AddNode->setMaximumSize(100, 40);

    ActiveNodes = new QComboBox;
    ActiveNodes->addItems(MyGraph.NodeHeaders);
    ActiveNodes->setMaximumSize(100,40);
    deleteLay->addWidget(ActiveNodes);

    DeleteNode = new QPushButton("Delete Node");
    deleteLay->addWidget(DeleteNode);

    deleteGroup->setLayout(deleteLay);
    deleteLay->setAlignment(Qt::AlignHCenter);
    deleteLay->setAlignment(deleteLay, Qt::AlignHCenter);

    buttonLay->addWidget(AddNode);
    buttonLay->addWidget(AddEdge);
    buttonLay->addWidget(deleteGroup);

    buttonLay->setAlignment(AddNode, Qt::AlignHCenter);
    buttonLay->setAlignment(AddEdge, Qt::AlignHCenter);
    buttonLay->setSpacing(5);

    ButtonGroup->setLayout(buttonLay);

    //Table setup

    QGroupBox *AdjacencyGroup = new QGroupBox("Adjacency Matrix");
    QGroupBox *IncidenceGroup = new QGroupBox("Incidence Matrix");
    QHBoxLayout *AdjacencyMatrixLay = new QHBoxLayout;
    QHBoxLayout *IncidenceMatrixLay = new QHBoxLayout;

    AdjacencyMatrix = new QTableWidget(1,1);
    AdjacencyMatrix->setMinimumSize(500,50);
    AdjacencyMatrix->setHorizontalHeaderLabels(MyGraph.NodeHeaders);

    AdjacencyMatrixLay->addWidget(AdjacencyMatrix);


    IncidenceMatrix = new QTableWidget(0,1);
    IncidenceMatrix->setMinimumSize(500,50);
    IncidenceMatrix->setHorizontalHeaderLabels(MyGraph.NodeHeaders);

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
    UpArea->addWidget(imageGroup);
    UpArea->addWidget(shortestWayGroup);
    UpArea->setAlignment(shortestWayGroup, Qt::AlignTop);
    MainArea->addItem(UpArea);
    MainArea->addItem(functionalArea);

    setLayout(MainArea);

    //connect setup
    connect(AddNode, SIGNAL(clicked()),SLOT(slotAddNode()));
    connect(AddNode, SIGNAL(clicked()),SLOT(slotUpdateIncMatrix()));
    connect(AddNode, SIGNAL(clicked()),SLOT(slotShortWay()));

    connect(AddEdge, SIGNAL(clicked()), SLOT(slotAddEdge()));

    connect(AdjacencyMatrix, SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(slotAdjacencyCellUpdate()));
    connect(AdjacencyMatrix, SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(slotUpdateIncMatrix()));
    connect(AdjacencyMatrix, SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(slotShortWay()));

    //connect(IncidenceMatrix, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(slotIncidenceCellUpdate()));
    //connect(IncidenceMatrix, SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(slotIncidenceCellUpdate()));
    //connect(IncidenceMatrix, SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(slotShortWay()));

    connect(DeleteNode, SIGNAL(clicked()),SLOT(slotDeleteNode()));
    connect(DeleteNode, SIGNAL(clicked()),SLOT(slotUpdateIncMatrix()));
    connect(DeleteNode, SIGNAL(clicked()),SLOT(slotShortWay()));

    connect(ShortestWayFrom, SIGNAL(currentIndexChanged(int)),SLOT(slotShortWay()));
    connect(ShortestWayTo, SIGNAL(currentIndexChanged(int)),SLOT(slotShortWay()));

    //add Image
    slotShortWay();
}

void InputMatrixData::slotAddNode()
{

    int AddedNode = MyGraph.NodeHeaders[((MyGraph.NodeHeaders.count())-1)].toInt()+1;

    MyGraph.AddNode();
    MyGraph.AddHeader(AddedNode);

    //AdjacencyMatrix setup

    AdjacencyMatrix->insertRow(AdjacencyMatrix->rowCount());
    AdjacencyMatrix->insertColumn(AdjacencyMatrix->columnCount());
    AdjacencyMatrix->setHorizontalHeaderLabels(MyGraph.NodeHeaders);
    AdjacencyMatrix->setVerticalHeaderLabels(MyGraph.NodeHeaders);

    //ComboBox setup
    ActiveNodes->addItem(QString::number(AddedNode));
    ShortestWayFrom->addItem(QString::number(AddedNode));
    ShortestWayTo->addItem(QString::number(AddedNode));
}

void InputMatrixData::slotAdjacencyCellUpdate()
{
    int item = (AdjacencyMatrix->currentItem()->text()).toInt();
    int CurrentColumn = (AdjacencyMatrix->currentColumn());
    int CurrentRow = (AdjacencyMatrix->currentRow());
    int column = MyGraph.NodeHeaders[CurrentColumn].toInt();
    int row = MyGraph.NodeHeaders[CurrentRow].toInt();
    int R1;
    QTableWidgetItem *item1(AdjacencyMatrix->item(CurrentColumn,CurrentRow));
    if (item1) {
        R1 = item1->text().toInt();
    } else {
        R1 = 0;
    }
    if (item!=0){
        if (R1==item){
            int index = MyGraph.GetEdgeIndex(column,row);
            while (index!=0){
                MyGraph.DeleteEdge(index);
                index = MyGraph.GetEdgeIndex(column,row);
            }
            index = MyGraph.GetEdgeIndex(row,column);
            while (index!=0){
                MyGraph.DeleteEdge(index);
                index = MyGraph.GetEdgeIndex(row,column);
            }
            MyGraph.AddBidirectionalEdge(column,row,item);
        }else{
            int index = MyGraph.GetEdgeIndex(column,row);
            if (index!=0){
                if (MyGraph.IsEdgeBiDirectional(index,column,row)){
                    MyGraph.DeleteEdge(index);
                    MyGraph.AddDirectionalEdge(column,row,R1);
                }
                if (item!=0)
                    MyGraph.AddDirectionalEdge(row,column,item);

            }else {
                index = MyGraph.GetEdgeIndex(row,column);
                if (index!=0){
                    if (MyGraph.IsEdgeBiDirectional(index,column,row)){
                        MyGraph.DeleteEdge(index);
                        MyGraph.AddDirectionalEdge(column,row,R1);
                    }
                }
                if (item!=0)
                    MyGraph.AddDirectionalEdge(row,column,item);
            }
        }
    }else {
        int index = MyGraph.GetEdgeIndex(column,row);
        if (index!=0){
            if (MyGraph.IsEdgeBiDirectional(index,column,row)){
                MyGraph.DeleteEdge(index);
                if (R1!=0)
                    MyGraph.AddDirectionalEdge(column,row,R1);
            } else {
                if (R1 == 0)
                    MyGraph.DeleteEdge(index);
            }
        }else {
            index = MyGraph.GetEdgeIndex(row,column);
            if (index!=0){
                if (MyGraph.IsEdgeBiDirectional(index,column,row)){
                    MyGraph.DeleteEdge(index);
                    if (R1!=0)
                        MyGraph.AddDirectionalEdge(column,row,R1);
                }else {
                    MyGraph.DeleteEdge(index);
                }
            }
        }
    }
}

void InputMatrixData::slotDeleteNode()
{

    QString Number = ActiveNodes->currentText();
    int DeleteIndexHeader = MyGraph.GetIndexFromHeader(Number.toInt());
    if (AdjacencyMatrix->columnCount()!=1){
        AdjacencyMatrix->removeColumn(DeleteIndexHeader);
        AdjacencyMatrix->removeRow(DeleteIndexHeader);
        MyGraph.DeleteHeader(Number.toInt());
        AdjacencyMatrix->setHorizontalHeaderLabels(MyGraph.NodeHeaders);
        AdjacencyMatrix->setVerticalHeaderLabels(MyGraph.NodeHeaders);
        MyGraph.DeleteNode(Number.toInt());
        ShortestWayTo->removeItem(ActiveNodes->currentIndex());
        ShortestWayFrom->removeItem(ActiveNodes->currentIndex());
        ActiveNodes->removeItem(ActiveNodes->currentIndex());        
    }
}

void InputMatrixData::slotUpdateIncMatrix()
{
    int CountOfRow = MyGraph.GetCountRowIncMat();
    int CountOfColumns = MyGraph.GetCountColumnIncMat();
    IncidenceMatrix->clearContents();
    if (CountOfColumns == 0)
        CountOfColumns = AdjacencyMatrix->columnCount();
    IncidenceMatrix->setColumnCount(CountOfColumns);
    IncidenceMatrix->setRowCount(CountOfRow);
    QStringList IncMatData = MyGraph.GetDataFromIncMat();
    int Row = -1;
    int Column = -1;
    int Value = 0;
    for (int i = 0; i < IncMatData.size(); i++){
        if (Row == -1)
            Row = IncMatData[i].toInt();
        else
            if (Column == -1)
                Column = IncMatData[i].toInt();
            else {
                Value = IncMatData[i].toInt();
                QTableWidgetItem *newItem = new QTableWidgetItem;
                newItem->setText(QString::number(Value));
                IncidenceMatrix->setItem(Row, Column, newItem);
                Row = Column = Value = -1;
            }
    }

    IncidenceMatrix->setHorizontalHeaderLabels(MyGraph.NodeHeaders);
}

void InputMatrixData::slotShortWay()
{
    QString From = ShortestWayFrom->currentText();
    QString To = ShortestWayTo->currentText();

    if ((From.toInt() == -1)||(To.toInt() == -1)){
        SetImage();
        return;
    }
    if (From != To){
        MyGraph.RunAlgoDijkstra(From.toInt());
        int Len = MyGraph.GetShortestWayTo(To.toInt());
        if (Len!=0)
            ShortestWayLen->setText(QString::number(Len));
        else
            ShortestWayLen->setText("No way :c");

    }else {
        ShortestWayLen->setText("0");
    }
    SetImage(From.toInt(), To.toInt());
}

void InputMatrixData::slotAddEdge()
{
    MyGraph.AddEdge();
    MyGraph.GetIncidenceMatrix();
    IncidenceMatrix->insertRow(IncidenceMatrix->rowCount());
}

void InputMatrixData::slotIncidenceCellUpdate()
{
    int item = (IncidenceMatrix->currentItem()->text()).toInt();
    int CurrentColumn = (IncidenceMatrix->currentColumn());
    int CurrentRow = (IncidenceMatrix->currentRow());
    //MyGraph.ChangeIncidenceMatrixCell(CurrentColumn+1, CurrentRow+1, item);

}

void InputMatrixData::SetImage(int From, int To)
{
    if (From!= 0){
        if (From != To){
            MyGraph.CreateDotFile(From, To);
        }else {
            MyGraph.CreateDotFile();
        }
    } else {
        MyGraph.CreateDotFile();
    }
    imageCreator->saveImageGV(MyGraph.GetDotFile());
}

void InputMatrixData::slotSetImage()
{
    QPixmap pixmap("graph.svg");
    Image->setPixmap(pixmap);
    remove("graph.svg");
}
