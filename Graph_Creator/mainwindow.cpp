#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deletenode.h"
#include "QHeaderView"

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

void MainWindow::on_AddColumn_clicked()
{
    MyGraph.AddNode();
    MyGraph.AddHeader(MyGraph.Headers[((MyGraph.Headers.count())-1)].toInt()+1);
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
    ui->tableWidget->setHorizontalHeaderLabels(MyGraph.Headers);
    ui->tableWidget->setVerticalHeaderLabels(MyGraph.Headers);
    MyGraph.GetDotFile();
    saveImageGV("graph");
    QPixmap pix("graph.svg");
    cout << "add"<< endl;
    ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
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
            }else {
                 index = MyGraph.GetEdgeIndex(row,column);
                if (index!=0){
                    if (MyGraph.IsEdgeBiDirectional(index,column,row)){
                        MyGraph.DeleteEdge(index);
                        MyGraph.AddDirectionalEdge(column,row,R1);
                    }
                }
            }
            MyGraph.AddDirectionalEdge(row,column,item);
        }
        //MyGraph.GetIncidenceMatrix();
    }else {
        if (item == NULL)
            item = 0;
        int index = MyGraph.GetEdgeIndex(row,column);
        if (index!=0){
            MyGraph.DeleteEdge(index);
        }
    }
    MyGraph.GetIncidenceMatrix();
    cout <<"------------------"<< endl;
    MyGraph.GetDotFile();
    saveImageGV("graph");
    QPixmap pix("graph.svg");
    ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_clicked()
{
    QString Number = ui->number->text();
    if (ui->tableWidget->columnCount()!=1){
        MyGraph.DeleteHeader(Number.toInt());
        ui->tableWidget->removeColumn(MyGraph.GetIndexFromHeader(Number.toInt())+1);
        ui->tableWidget->removeRow(MyGraph.GetIndexFromHeader(Number.toInt())+1);
        ui->tableWidget->setHorizontalHeaderLabels(MyGraph.Headers);
        ui->tableWidget->setVerticalHeaderLabels(MyGraph.Headers);
        MyGraph.DeleteNode(Number.toInt());
        MyGraph.GetDotFile();
        saveImageGV("graph");
        QPixmap pix("graph.svg");
        ui->label->setPixmap(pix.scaled(301,441,Qt::KeepAspectRatio));
    }
    ui->number->setText("");
}
