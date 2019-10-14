#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Graph.h>
#include <QMainWindow>
#include <graphviz/gvc.h>
#include <QString>
#include "deletenode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Graph MyGraph;
    int Cache = 0;
private slots:
    void OnCellChangeds(int);
    void OnCellUpdate();
    void ShortestWay();
    void on_pushButton_clicked();

    void on_AddNode_clicked();

    void on_Cycles_clicked();

private:
    Ui::MainWindow *ui;
    DeleteNode *delnode;
};

#endif // MAINWINDOW_H
