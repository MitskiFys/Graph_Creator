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

private slots:

    void on_AddColumn_clicked();
    void OnCellChangeds(int);
    void OnCellUpdate();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DeleteNode *delnode;
};

#endif // MAINWINDOW_H
