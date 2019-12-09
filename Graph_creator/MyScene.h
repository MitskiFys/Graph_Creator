#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
class MyScene : public QGraphicsScene {
  Q_OBJECT
public:
    explicit MyScene(QObject *parent = nullptr):QGraphicsScene(parent)
    {

    }
protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  QGraphicsItem *m_activeItem = nullptr;
  QGraphicsItem *m_firstItem = nullptr;
  QGraphicsItem *m_secondItem = nullptr;
private:
  int nodeHeaders = 1;
  int radius = 30;
  std::map<QGraphicsItem*, std::vector<QGraphicsItem*>*> lines;
  std::map<QGraphicsItem*, std::vector<QGraphicsLineItem*>*> edges;
  std::map<int, QGraphicsItem*> nods;
  std::map<int,int> xCoords;
  std::map<int,int> yCoords;
  void setLine(QGraphicsLineItem* line);
  void addNode(QGraphicsSceneMouseEvent *event);
  int getX(QGraphicsItem* item);
  int getY(QGraphicsItem* item);
  void addLine();
  std::vector<QGraphicsItem*> getNods();
  void selectItem(QGraphicsSceneMouseEvent *event);
  void deSelectItem();
  int getNodeHeader(QGraphicsItem* item);
signals:
  void addNode();
  void connectNods(int first, int second);
public slots:
  void slotDeleteNode(int index);

};

#endif // MYSCENE_H
