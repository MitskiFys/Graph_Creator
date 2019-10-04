#include "deletenode.h"
#include "ui_deletenode.h"

DeleteNode::DeleteNode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteNode)
{
    ui->setupUi(this);
}

DeleteNode::~DeleteNode()
{
    delete ui;
}

void DeleteNode::on_pushButton_clicked()
{

    close();
}
