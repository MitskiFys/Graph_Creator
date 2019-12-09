#include "MyEllipse.h"

#include <QPainter>
#include <cmath>

MyEllipse::MyEllipse(size_t radius, QColor color, QObject *parent, int header)
    : QObject(parent), QGraphicsItem(),
      m_radius(radius), m_color(color),Header(header) {
}

QRectF MyEllipse::boundingRect() const {
    return QRectF(QPoint(-m_radius, -m_radius), QPoint(m_radius, m_radius));
}

void MyEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setPen(Qt::black);
    painter->setBrush(m_color);
    painter->drawEllipse(-m_radius,-m_radius,m_radius*2,m_radius*2);
    painter->setFont(QFont("Times", 15, QFont::Bold));
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(Header));
    painter->setRenderHint(QPainter::Antialiasing,true);
//    painter->drawTe
}

QPolygonF MyEllipse::polygon() const {
  QPolygonF polygon;
  size_t small_radius = m_radius/2;
  double step = 360./5, angle_deg = 0;
  for (size_t count = 0; count < 5; ++count) {
    double angle_rad = angle_deg*M_PI/180;
    QPointF outerPoint(m_radius*cos(angle_rad), m_radius*sin(angle_rad));
    QPointF innerPoint(small_radius*cos(angle_rad), small_radius*sin(angle_rad));
    polygon << outerPoint << innerPoint;
    angle_deg += step;
  }
  return polygon;
}
