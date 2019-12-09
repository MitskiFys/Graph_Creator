#ifndef WIDGETSHOWIMAGE_H
#define WIDGETSHOWIMAGE_H

#include "MyView.h"
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsPixmapItem>


class WidgetShowImage : public QWidget
{
    Q_OBJECT
public:
    WidgetShowImage(QWidget* pwgt = nullptr);
};

#endif // WIDGETSHOWIMAGE_H
