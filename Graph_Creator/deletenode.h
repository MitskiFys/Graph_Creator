#ifndef DELETENODE_H
#define DELETENODE_H

#include <QDialog>

namespace Ui {
class DeleteNode;
}

class DeleteNode : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteNode(QWidget *parent = 0);
    ~DeleteNode();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DeleteNode *ui;
};

#endif // DELETENODE_H
