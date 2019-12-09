#ifndef MYELLIPSE_H
#define MYELLIPSE_H


#include <QGraphicsItem>
#include <QObject>
class MyEllipse : public QObject, public QGraphicsItem {
  Q_OBJECT
public:
  MyEllipse(size_t radius, QColor color, QObject* parent, int header);
protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
  QRectF boundingRect() const override;
private:
  int Header;
  QPolygonF polygon() const;
protected:
  size_t m_radius;
  QColor m_color;
};

#endif // MYELLIPSE_H
