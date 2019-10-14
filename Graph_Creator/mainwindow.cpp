#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deletenode.h"
#include "QHeaderView"
#include <unistd.h>
#include <QThread>

bool saveImageGV(std::string file_path){
    GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen((file_path+".dot").c_str(), "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "svg", fopen((file_path+".svg").c_str(), "w"));
    gvFreeLayout(gvc, g);
    agclose(g);
    return (gvFreeContext(gvc));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(OnCellUpdate()));
    connect (ui->FirstNode, SIGNAL(textChanged(QString)),this,SLOT(ShortestWay()));
    connect (ui->SecondNode, SIGNAL(textChanged(QString)),this,SLOT(ShortestWay()));

    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(1);
    MyGraph.AddHeader(1);
    ui->tableWidget->setHorizontalHeaderLabels(MyGraph.Headers);
    ui->tableWidget->setVerticalHeaderLabels(MyGraph.Headers);
    MyGraph.AddNode();

    MyGraph.GetDotFile();
    saveImageGV("graph");
    QPixmap pix("graph.svg");
    ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::OnCellChangeds(int row)
{
    cout << "hi"<<endl;
}

void MainWindow::OnCellUpdate()
{
    int item = (ui->tableWidget->currentItem()->text()).toInt();
    int CurrentColumn = (ui->tableWidget->currentColumn());
    int CurrentRow = (ui->tableWidget->currentRow());
    int column = MyGraph.Headers[CurrentColumn].toInt();
    int row = MyGraph.Headers[CurrentRow].toInt();
    int R1;
    QTableWidgetItem *item1(ui->tableWidget->item(CurrentColumn,CurrentRow));
    if (item1) {
        R1 = item1->text().toInt();
    } else {
        R1 = 0;
    }
    if ((item!=0)&&(item!= NULL)){
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
            //MyGraph.AddDirectionalEdge(row,column,item);
        }
    }else {
        if (item == NULL)
            item = 0;
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
    if ((ui->FirstNode->text()!= NULL)&&(ui->SecondNode->text()!=0)){
        MyGraph.RunAlgoDijkstra(ui->FirstNode->text().toInt());
        if ((MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())==0)and(ui->FirstNode->text().toInt()!=ui->SecondNode->text().toInt()))
            ui->Length->setText("No way");
        else
            ui->Length->setText(QString::number(MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())));        MyGraph.GetDotFile(ui->FirstNode->text().toInt(),ui->SecondNode->text().toInt());
    }else
        MyGraph.GetDotFile();
    saveImageGV("graph");
    QPixmap pix("graph.svg");
    ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
}

void MainWindow::ShortestWay()
{
    //     QThread::sleep(10000);

    if (MyGraph.Headers.last().toInt()<ui->FirstNode->text().toInt()){
        ui->FirstNode->setText("");
        return;
    }

    if (MyGraph.Headers.last().toInt() < ui->SecondNode->text().toInt()){
        ui->SecondNode->setText("");
        return;
    }
    if ((ui->FirstNode->text()!=NULL)&&(ui->FirstNode->text().toInt()!=0)&&(ui->FirstNode->text().toInt()!=Cache)&&((ui->SecondNode->text()==NULL)||(ui->SecondNode->text().toInt()==0))){
        MyGraph.RunAlgoDijkstra(ui->FirstNode->text().toInt());
        Cache = ui->FirstNode->text().toInt();
    } else if ((ui->FirstNode->text().toInt()==Cache)&&((ui->SecondNode->text()==NULL)||(ui->SecondNode->text().toInt()==0))){
        MyGraph.GetDotFile();

        saveImageGV("graph");
        QPixmap pix("graph.svg");
        ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
        ui->Length->setText("");
        remove("graph.svg");

    } else if ((ui->FirstNode->text().toInt()==Cache)&&(ui->SecondNode->text()!=NULL)&&(ui->SecondNode->text().toInt()!=0)){
        MyGraph.GetDotFile(ui->FirstNode->text().toInt(),ui->SecondNode->text().toInt());
        saveImageGV("graph");
        QPixmap pix("graph.svg");
        ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
        if ((MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())==0)and(ui->FirstNode->text().toInt()!=ui->SecondNode->text().toInt()))
            ui->Length->setText("No way");
        else
            ui->Length->setText(QString::number(MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())));
    } else if((ui->FirstNode->text()==NULL)||(ui->FirstNode->text().toInt()==0)){
        MyGraph.GetDotFile();
        saveImageGV("graph");
        QPixmap pix("graph.svg");
        ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
        ui->Length->setText("");
        remove("graph.svg");
    } else if (((ui->FirstNode->text()!=NULL)||(ui->FirstNode->text().toInt()!=0))&&(ui->FirstNode->text().toInt()!=Cache)&&(ui->SecondNode->text()!=NULL)&&(ui->SecondNode->text().toInt()!=0)){
        MyGraph.RunAlgoDijkstra(ui->FirstNode->text().toInt());
        Cache = ui->FirstNode->text().toInt();
        MyGraph.GetDotFile(ui->FirstNode->text().toInt(),ui->SecondNode->text().toInt());
        saveImageGV("graph");
        QPixmap pix("graph.svg");
        ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
        if ((MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())==0)and(ui->FirstNode->text().toInt()!=ui->SecondNode->text().toInt()))
            ui->Length->setText("No way");
        else
            ui->Length->setText(QString::number(MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())));
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString Number = ui->number->text();
    if (ui->tableWidget->columnCount()!=1){
        cout << MyGraph.GetIndexFromHeader(Number.toInt()) << endl;
        ui->tableWidget->removeColumn(MyGraph.GetIndexFromHeader(Number.toInt()));
        ui->tableWidget->removeRow(MyGraph.GetIndexFromHeader(Number.toInt()));
        MyGraph.DeleteHeader(Number.toInt());
        ui->tableWidget->setHorizontalHeaderLabels(MyGraph.Headers);
        ui->tableWidget->setVerticalHeaderLabels(MyGraph.Headers);
        MyGraph.DeleteNode(Number.toInt());
        if ((ui->FirstNode->text()!= NULL)&&(ui->SecondNode->text()!=0)&&(Number!=ui->FirstNode->text())&&(Number!=ui->SecondNode->text())){
            MyGraph.RunAlgoDijkstra(ui->FirstNode->text().toInt());
            if ((MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())==0)and(ui->FirstNode->text().toInt()!=ui->SecondNode->text().toInt()))
                ui->Length->setText("No way");
            else
                ui->Length->setText(QString::number(MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())));            MyGraph.GetDotFile(ui->FirstNode->text().toInt(),ui->SecondNode->text().toInt());
        }else if((ui->FirstNode->text()== NULL)&&(ui->SecondNode->text()==NULL))
        {
            MyGraph.GetDotFile();
        }else if((Number==ui->FirstNode->text())||(Number==ui->SecondNode->text())){
            ui->FirstNode->setText("");
            ui->SecondNode->setText("");
            ui->Length->setText("");
            MyGraph.GetDotFile();
        }
        saveImageGV("graph");
        QPixmap pix("graph.svg");
        ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
    }
    ui->number->setText("");
}

void MainWindow::on_AddNode_clicked()
{
    MyGraph.AddNode();
    MyGraph.AddHeader(MyGraph.Headers[((MyGraph.Headers.count())-1)].toInt()+1);
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
    ui->tableWidget->setHorizontalHeaderLabels(MyGraph.Headers);
    ui->tableWidget->setVerticalHeaderLabels(MyGraph.Headers);
    if ((ui->FirstNode->text()!= NULL)&&(ui->SecondNode->text()!=0)){
        MyGraph.RunAlgoDijkstra(ui->FirstNode->text().toInt());
        if ((MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())==0)and(ui->FirstNode->text().toInt()!=ui->SecondNode->text().toInt()))
            ui->Length->setText("No way");
        else
            ui->Length->setText(QString::number(MyGraph.GetShortestWayTo(ui->SecondNode->text().toInt())));        MyGraph.GetDotFile(ui->FirstNode->text().toInt(),ui->SecondNode->text().toInt());
    }else
        MyGraph.GetDotFile();
    saveImageGV("graph");
    QPixmap pix("graph.svg");
    cout << "add"<< endl;
    ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
}

void MainWindow::on_Cycles_clicked()
{
    ui->CountOfCyrcle->setText(QString::number(MyGraph.GetCountOfCycle()));
}
