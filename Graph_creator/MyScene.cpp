#include "MyEllipse.h"
#include "MyScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <iostream>
#include <cmath>



void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsScene::mousePressEvent(event);
    m_activeItem = mouseGrabberItem();
    std:: cout << event->scenePos().x();
    if (m_activeItem == nullptr){
        m_activeItem = mouseGrabberItem();
        addNode(event);
    }

    if (mouseGrabberItem() != nullptr){
        if (m_firstItem == nullptr){
            m_firstItem = mouseGrabberItem();
            m_firstItem->setFocus();
            return;
        }
        m_secondItem = mouseGrabberItem();
        if (m_secondItem != m_firstItem){
            addLine();
        } else {
            deSelectItem();
        }
    }
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    m_activeItem = mouseGrabberItem();
    if (!m_activeItem)
        return;
    m_firstItem = m_activeItem;

    std::vector<QGraphicsItem*> nodes = getNods();
    std::vector<std::vector<QGraphicsLineItem*>::iterator> todelete;
    std::vector<QGraphicsLineItem*>* nodsFirst = edges[m_firstItem];
    for (int i = 0; i < nodes.size(); i++){
        m_secondItem = nodes[i];

        std::vector<QGraphicsLineItem*>* nodsSecond = edges[m_secondItem];
        for (std::vector<QGraphicsLineItem*>::iterator iter = nodsFirst->begin(); iter != nodsFirst->end(); iter++){
            QGraphicsItem* delitem = (*iter);
            for(std::vector<QGraphicsLineItem*>::iterator iterf = nodsSecond->begin(); iterf != nodsSecond->end(); iterf++){
                if (delitem == (*iterf)){
                    nodsSecond->erase(iterf);
                    break;
                }
            }
        }

    }
    for (std::vector<QGraphicsLineItem*>::iterator iter = nodsFirst->begin(); iter != nodsFirst->end(); iter++){
        removeItem((*iter));
    }
    if (nodes.size()!=0){
        std::vector<QGraphicsLineItem*>* nullVector = new std::vector<QGraphicsLineItem*>;
        delete(edges[m_activeItem]);
        edges[m_activeItem] = nullVector;
        for (int i = 0; i < nodes.size(); i++){
            m_secondItem = nodes[i];
            QColor color(150,150,150);
            QGraphicsLineItem* line = new QGraphicsLineItem;
            line->setPen(QPen(color,3));
            setLine(line);
            addItem(line);
            edges[m_activeItem]->push_back(line);
            edges[nodes[i]]->push_back(line);
        }
    }
    m_firstItem = nullptr;
    m_secondItem = nullptr;
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    selectItem(event);

}

std::vector<QGraphicsItem *> MyScene::getNods()
{
    std::vector<QGraphicsItem*> returnNods;
    std::vector<QGraphicsLineItem*>* activeEdges = edges[m_activeItem];//
    for (std::vector<QGraphicsLineItem*>::iterator iterf = activeEdges->begin(); iterf!=activeEdges->end();++iterf){
        for (std::map<QGraphicsItem*, std::vector<QGraphicsLineItem*>*>::iterator iter = edges.begin(); iter != edges.end(); ++iter){
            std::vector<QGraphicsLineItem*>* vec = (*iter).second;
            if ((*iter).first != m_activeItem){
                for (std::vector<QGraphicsLineItem*>::iterator iterv = vec->begin(); iterv != vec->end(); ++iterv){
                    if ((*iterf)==(*iterv)){
                        returnNods.push_back((*iter).first);
                        break;
                    }
                }
            }
        }
    }
    //proshu proshenie za eto



    return returnNods;
}

void MyScene::selectItem(QGraphicsSceneMouseEvent *event)
{
    if (m_firstItem != nullptr && m_secondItem == nullptr){
        QColor color(153,255,153);
        m_activeItem = nullptr;
        int header = getNodeHeader(m_firstItem);
        m_activeItem = new MyEllipse(radius, color, this, header);

        if (m_activeItem == nullptr)
            return;

        m_activeItem->setFlag(QGraphicsItem::ItemIsMovable);
        m_activeItem->setPos(m_firstItem->x(),m_firstItem->y());
        removeItem(m_firstItem);
        nods[header] = m_activeItem;

        std::vector<QGraphicsLineItem*>* copyNodsFirst = edges[m_firstItem];

        edges.erase(m_firstItem);


        addItem(m_activeItem);


        edges.insert(std::make_pair(m_activeItem, copyNodsFirst));
        m_firstItem = m_activeItem;
    }
}

void MyScene::deSelectItem()
{

    QColor color(150,150,150);
    m_activeItem = nullptr;
    int header = getNodeHeader(m_firstItem);
    m_activeItem = new MyEllipse(radius, color, this, header);

    if (m_activeItem == nullptr)
        return;

    m_activeItem->setFlag(QGraphicsItem::ItemIsMovable);
    m_activeItem->setPos(m_firstItem->x(),m_firstItem->y());
    removeItem(m_firstItem);
    nods[header] = m_activeItem;

    std::vector<QGraphicsLineItem*>* copyNodsFirst = edges[m_firstItem];

    edges.erase(m_firstItem);

    addItem(m_activeItem);

    edges.insert(std::make_pair(m_activeItem, copyNodsFirst));
    m_firstItem = nullptr;
    m_secondItem = nullptr;
    m_activeItem = nullptr;

}

int MyScene::getNodeHeader(QGraphicsItem *item)
{
    for (std::map<int, QGraphicsItem*>::iterator iter = nods.begin(); iter != nods.end(); iter++){
        if ((*iter).second == item)
            return (*iter).first;
    }
}

void MyScene::slotDeleteNode(int index)
{
    QGraphicsItem* node;
    for (std::map<int, QGraphicsItem*>::iterator iter = nods.begin(); iter != nods.end(); iter++){
        if ((*iter).first == index){
            node = (*iter).second;
        }
    }

    std::vector<QGraphicsLineItem*>* activeEdges;

    for (std::map<QGraphicsItem*, std::vector<QGraphicsLineItem*>*>::iterator iter = edges.begin(); iter != edges.end(); iter++ ){
        if ((*iter).first == node){
            activeEdges = (*iter).second;
        }
    }

    for (int i = 0; i < activeEdges->size(); i++){
        removeItem((*activeEdges)[i]);
        //delete ((*activeEdges)[i]);
    }
    if (index == nodeHeaders){
        nodeHeaders--;
    }
    removeItem(node);
    edges.erase(node);
    nods.erase(index);
    delete(node);
}

void MyScene::addNode(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    xCoords.insert(std::make_pair(nodeHeaders, event->scenePos().x()));
    yCoords.insert(std::make_pair(nodeHeaders, event->scenePos().y()));

    QPointF pos = event->scenePos();
    QColor color(150,150,150);

    m_activeItem = nullptr;
    m_activeItem = new MyEllipse(radius, color, this, nodeHeaders);

    if (nullptr == m_activeItem)
        return;
    nods.insert(std::make_pair(nodeHeaders, m_activeItem));

    addItem(m_activeItem);

    m_activeItem->setFlag(QGraphicsItem::ItemIsMovable);
    m_activeItem->setPos(pos);

    std::vector<QGraphicsLineItem*>* line = new std::vector<QGraphicsLineItem*>;
    edges.insert(std::make_pair(m_activeItem, line));
    nodeHeaders++;

    m_activeItem = nullptr;
    if (nodeHeaders > 2)
    emit addNode();
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);
    if (nullptr == m_activeItem)
        return;
    switch (event->key()) {
    case Qt::Key::Key_A:
        m_activeItem->moveBy(-5, 0);
        break;
    case Qt::Key::Key_S:
        m_activeItem->moveBy(0, 5);
        break;
    case Qt::Key::Key_D:
        m_activeItem->moveBy(5, 0);
        break;
    case Qt::Key::Key_W:
        m_activeItem->moveBy(0, -5);
        break;
    }
}

int MyScene::getX(QGraphicsItem *item)
{
    for (std::map<int, QGraphicsItem*>::iterator iter = nods.begin(); iter != nods.end(); ++iter){
        if ((*iter).second == item)
            return xCoords[(*iter).first];
    }
    return 0;
}

int MyScene::getY(QGraphicsItem *item)
{
    for (std::map<int, QGraphicsItem*>::iterator iter = nods.begin(); iter != nods.end(); ++iter){
        if ((*iter).second == item)
            return yCoords[(*iter).first];
    }
    return 0;
}

void MyScene::addLine()
{
    QColor color(150,150,150);
    QGraphicsLineItem* line = new QGraphicsLineItem;
    line->setPen(QPen(color,3));
    setLine(line);
    addItem(line);


    edges[m_firstItem]->push_back(line);
    edges[m_secondItem]->push_back(line);

    //    edges.insert(std::make_pair(m_firstItem, line));
    //    edges.insert(std::make_pair(m_secondItem, line));
    emit connectNods(getNodeHeader(m_firstItem), getNodeHeader(m_secondItem));
    deSelectItem();
    m_firstItem = nullptr;
    m_secondItem = nullptr;

}

void MyScene::setLine(QGraphicsLineItem* line)
{
    int x1 = m_firstItem->x();
    int y1 = m_firstItem->y();
    int x2 = m_secondItem->x();
    int y2 = m_secondItem->y();
    if(x1 > x2){
        int swap = x1;
        x1 = x2;
        x2 = swap;
        swap = y1;
        y1 = y2;
        y2 = swap;
    }
    int dx = x2-x1;
    int dy = y2-y1;
    double k = (double)dy/dx;//y=kx+c
    double c = y1 - k * x1;

    double koefA = (1 + pow(k, 2));
    double koefB = (2 * x1 - 2 * k * c + 2 * y1 * k);
    double koefC = (pow(x1,2) + pow(c,2) - 2 * y1 * c + pow(y1,2) - pow(radius, 2));
    double diskr = pow(koefB,2) - 4 * koefA * koefC;

    double xp1 = (koefB + sqrt(diskr))/(2 * koefA);
    double yp1 = k*xp1 + c;

    koefB = (2 * x2 - 2 * k * c + 2 * y2 * k);
    koefC = (pow(x2,2) + pow(c,2) - 2 * y2 * c + pow(y2,2) - pow(radius, 2));
    diskr = pow(koefB,2) - 4 * koefA * koefC;
    double xp2 = (koefB - sqrt(diskr))/(2 * koefA);
    double yp2 = k*xp2 + c;
    std::cout << xp2 << std::endl;
    line->setLine(xp1,yp1,xp2,yp2);
}
