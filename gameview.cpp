#include "gameview.h"

#include <QDebug>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QScreen>
GameView::GameView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent) {
    // centerOn will make problems
    resize(sizeHint());
    setSceneRect(0, 0, sizeHint().width() + 10, sizeHint().height() + 10);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QSize GameView::sizeHint() const {
    const QRect availableGeometry = screen()->availableGeometry();
    return QSize(availableGeometry.width() * 2 / 3,
                 availableGeometry.height() * 2 / 3);
}
/*for debug*/
// void GameView::mousePressEvent(QMouseEvent* event) {
//    QPoint viewPos = event->pos();
//    qDebug() << "viewPos: " << viewPos;
//    QPointF scenePos = mapToScene(viewPos);
//    qDebug() << "scenePos: " << scenePos;
//    QGraphicsItem* item = scene()->itemAt(scenePos, QTransform());
//    if (item) {
//        QPointF itemPos = item->mapFromScene(scenePos);
//        qDebug() << "itemPos: " << itemPos;
//    }
//    QGraphicsView::mousePressEvent(event);
//}
