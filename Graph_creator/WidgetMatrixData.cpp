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

    connect(IncidenceMatrix, SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(slotIncidenceCellUpdate()));
    connect(IncidenceMatrix, SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(slotUpdateAdjMatrix()));
    connect(IncidenceMatrix, SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(slotShortWay()));

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
    Signal = true;
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
    Signal = false;
}

void InputMatrixData::slotAdjacencyCellUpdate()
{
    if (Signal){
        return;
    }
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
    if (Signal)
        return;
    Signal = true;
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
    Signal = false;
}

void InputMatrixData::slotUpdateAdjMatrix()
{
    if (Signal)
        return;
    Signal = true;
    int CountOfColumns = MyGraph.GetCountColumnAdjMat();
    AdjacencyMatrix->clearContents();
    AdjacencyMatrix->setColumnCount(CountOfColumns);
    AdjacencyMatrix->setRowCount(CountOfColumns);
    QStringList AdjMatData = MyGraph.GetDataFromAdjMat();
    int Row = -1;
    int Column = -1;
    int Value = 0;
    for (int i = 0; i < AdjMatData.size(); i++){
        if (Row == -1)
            Row = AdjMatData[i].toInt();
        else
            if (Column == -1)
                Column = AdjMatData[i].toInt();
            else {
                Value = AdjMatData[i].toInt();
                QTableWidgetItem *newItem = new QTableWidgetItem;
                newItem->setText(QString::number(Value));

                AdjacencyMatrix->setItem(Row, Column, newItem);
                Row = Column = Value = -1;
            }
    }

    AdjacencyMatrix->setHorizontalHeaderLabels(MyGraph.NodeHeaders);
    AdjacencyMatrix->setVerticalHeaderLabels(MyGraph.NodeHeaders);
    Signal = false;
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
    //MyGraph.GetIncidenceMatrix();
    IncidenceMatrix->insertRow(IncidenceMatrix->rowCount());
}

void InputMatrixData::slotIncidenceCellUpdate()
{
    if (Signal){
        return;
    }
    Signal = true;
    QTableWidgetItem *newItem = new QTableWidgetItem;
    int item = (IncidenceMatrix->currentItem()->text()).toInt();
    int CurrentColumn = (IncidenceMatrix->currentColumn());
    int CurrentRow = (IncidenceMatrix->currentRow());
    QStringList OtherItems = MyGraph.GetSecondValueInRowFromIncMatrix(CurrentRow, CurrentColumn);
    int Value = abs(item);
    if (item != 0){
        item = item / abs(item);
    }
    if (OtherItems.size() == 0){
        if (item != -1)
            item = -1;
        newItem->setText(QString::number(item));
        //Signal = true;
        IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem);
        MyGraph.ChangeAdjacencyMatrixCell(CurrentColumn+1, CurrentColumn+1, Value);
        MyGraph.ChangeIncidenceMatrixCell(CurrentRow+1, CurrentColumn+1, item);

    }else if (OtherItems.size() == 2){
        int PrevNods = OtherItems[0].toInt();
        int PrevItem = OtherItems[1].toInt();
        if (PrevNods == CurrentColumn + 1){
            if (item == 0)
                item = 0;
                else if (item != -1)
                item = -1;
            MyGraph.ChangeAdjacencyMatrixCell(PrevNods, PrevNods, 0);
            MyGraph.ChangeAdjacencyMatrixCell(PrevNods, PrevNods, Value);
            newItem->setText(QString::number(item));
            //Signal = true;
            IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem);
            MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1,CurrentColumn +1, item );
        } else if (item == -1){

            MyGraph.ChangeAdjacencyMatrixCell(PrevNods, PrevNods, 0);
            MyGraph.ChangeAdjacencyMatrixCell(PrevNods, CurrentColumn + 1, Value);
            MyGraph.ChangeAdjacencyMatrixCell(CurrentColumn + 1, PrevNods,  Value);

            newItem->setText(QString::number(item));
            //Signal = true;
            IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem);
            MyGraph.ChangeIncidenceMatrixCell( CurrentRow+1, CurrentColumn+1, item);

        } else if (item == 1){

            MyGraph.ChangeAdjacencyMatrixCell(PrevNods, PrevNods, 0);
            MyGraph.ChangeAdjacencyMatrixCell(CurrentColumn + 1, PrevNods,  Value);

            newItem->setText(QString::number(item));
            //Signal = true;
            IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem);
            MyGraph.ChangeIncidenceMatrixCell( CurrentRow+1, CurrentColumn+1, item);
        } else if (item == 0){
            MyGraph.ChangeIncidenceMatrixCell(CurrentRow+1, CurrentColumn+1, 0);
            MyGraph.ChangeIncidenceMatrixCell(CurrentRow+1, PrevNods, -1);

            MyGraph.ChangeAdjacencyMatrixCell(CurrentColumn + 1, PrevNods, 0);
            MyGraph.ChangeAdjacencyMatrixCell(PrevNods, CurrentColumn + 1, 0);

            newItem->setText(QString::number(-1));
            //Signal = true;
            IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem);
        }

    } else if (OtherItems.size() == 4) {
        int FirstNode = OtherItems[0].toInt();
        int FirstItem = OtherItems[1].toInt();
        int SecondNode = OtherItems[2].toInt();
        int SecondItem = OtherItems[3].toInt();

        if (item == 0){
            MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, CurrentColumn+1, 0);
            MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, 0);
            MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode,0);
            newItem->setText("");

            //MyGraph.ChangeAdjacencyMatrixCell(SecondNode, SecondNode,1);
            //Signal = true;
            IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem);
            if (CurrentColumn + 1 == FirstNode){
                CurrentColumn = SecondNode;
                QTableWidgetItem* newItem1 = new QTableWidgetItem;
                newItem1->setText(QString::number(-1));
                //Signal = true;
                IncidenceMatrix->setItem(CurrentRow, SecondNode - 1, newItem1);
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, SecondNode, -1);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, SecondNode, 1);


            } else if (CurrentColumn + 1 == SecondNode){
                CurrentColumn = FirstNode;
                QTableWidgetItem* newItem1 = new QTableWidgetItem;
                newItem1->setText(QString::number(-1));
                //Signal = true;
                IncidenceMatrix->setItem(CurrentRow, FirstNode - 1, newItem1);
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, FirstNode, -1);
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, FirstNode, 1);
            } /*else {
                QTableWidgetItem* newItem1 = new QTableWidgetItem;
                newItem1->setText("");
                //Signal = true;
                IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem1);
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, CurrentColumn + 1, 0);
            }*/

        } else if(item == 1){
            QTableWidgetItem* newItem2 = new QTableWidgetItem;
            newItem2->setText(QString::number(item));
            //Signal = true;
            IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem2);
            if (CurrentColumn + 1 == FirstNode){
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, Value);
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, SecondNode, -1);//Меняем все в матрице инцидентности
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, CurrentColumn +1, 1);

                QTableWidgetItem* newItem1 = new QTableWidgetItem;
                newItem1->setText(QString::number(-1));
                //Signal = true;
                IncidenceMatrix->setItem(CurrentRow, SecondNode - 1, newItem1);

            }else if(CurrentColumn + 1 == SecondNode){
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode, Value);

                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, FirstNode, -1);//Меняем все в матрице инцидентности
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, CurrentColumn +1, 1);
                QTableWidgetItem* newItem1 = new QTableWidgetItem;
                newItem1->setText(QString::number(-1));
                //Signal = true;
                IncidenceMatrix->setItem(CurrentRow, FirstNode - 1, newItem1);
            }else {
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode, 0);//Очищяем связи с первой вершиной
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, FirstNode, 0);

                QTableWidgetItem* newItem1 = new QTableWidgetItem;
                newItem1->setText("");
                Signal = true;
                IncidenceMatrix->setItem(CurrentRow, FirstNode -1, newItem1);

                MyGraph.ChangeAdjacencyMatrixCell(CurrentColumn + 1, SecondNode, Value);
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, SecondNode, -1);
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, CurrentColumn + 1, 1);

                newItem->setText(QString::number(-1));
                //Signal = true;
                IncidenceMatrix->setItem(CurrentRow, SecondNode -1, newItem);
            }

        }else if (item == -1) {
            QTableWidgetItem* newItem2 = new QTableWidgetItem;
            newItem2->setText(QString::number(item));
            //Signal = true;
            IncidenceMatrix->setItem(CurrentRow, CurrentColumn, newItem2);
            MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, CurrentColumn +1, -1);
            if (CurrentColumn + 1 == FirstNode){
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, Value);
                if (SecondItem == -1)
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode,  Value);

            }else if(CurrentColumn + 1 == SecondNode){
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode, Value);
                if (FirstItem == -1)
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode,  Value);
            }else {
                MyGraph.ChangeAdjacencyMatrixCell(FirstNode, SecondNode, 0);
                MyGraph.ChangeAdjacencyMatrixCell(SecondNode, FirstNode, 0);//Очищяем связи с первой вершиной
                MyGraph.ChangeIncidenceMatrixCell(CurrentRow + 1, FirstNode, 0);

                QTableWidgetItem* newItem1 = new QTableWidgetItem;
                newItem1->setText("");
                //Signal = true;
                IncidenceMatrix->setItem(CurrentRow, FirstNode -1, newItem1);

                MyGraph.ChangeAdjacencyMatrixCell(CurrentColumn + 1, SecondNode, Value);
            }

        }
    }
    MyGraph.GetAdjacencyMatrix();
    MyGraph.GetIncidenceMatrix();
    Signal = false;
    cout << Signal << endl;
}

void InputMatrixData::SetImage(int From, int To)
{
    if (Signal)
        return;
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
