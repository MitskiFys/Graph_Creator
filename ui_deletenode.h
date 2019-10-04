/********************************************************************************
** Form generated from reading UI file 'deletenode.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETENODE_H
#define UI_DELETENODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DeleteNode
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *DeleteNode)
    {
        if (DeleteNode->objectName().isEmpty())
            DeleteNode->setObjectName(QStringLiteral("DeleteNode"));
        DeleteNode->resize(382, 258);
        label = new QLabel(DeleteNode);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 80, 281, 21));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);
        lineEdit = new QLineEdit(DeleteNode);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(140, 120, 91, 61));
        QFont font1;
        font1.setPointSize(20);
        lineEdit->setFont(font1);
        pushButton = new QPushButton(DeleteNode);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 190, 89, 25));

        retranslateUi(DeleteNode);

        QMetaObject::connectSlotsByName(DeleteNode);
    } // setupUi

    void retranslateUi(QDialog *DeleteNode)
    {
        DeleteNode->setWindowTitle(QApplication::translate("DeleteNode", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DeleteNode", "Which node do you want to delete?", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DeleteNode", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DeleteNode: public Ui_DeleteNode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETENODE_H
