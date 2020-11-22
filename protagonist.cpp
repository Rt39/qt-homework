#include "protagonist.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPainter>
#include <QtMath>
Protagonist::Protagonist() {
    pic_normal.load(":/entity/protagonist/normal");
    pic_walk1.load(":/entity/protagonist/walk1");
    pic_walk2.load(":/entity/protagonist/walk2");

    setFlag(QGraphicsObject::ItemIsFocusable);
    setFocus();

    sword.setParentItem(this);
    sword.setPos(111, 0);
    sword.setZValue(1);
    sword.setTransformOriginPoint(19, 137);
    sword.setVisible(false);
}

QRectF Protagonist::boundingRect() const { return QRectF(0, 0, 111, 210); }

void Protagonist::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                        QWidget*) {
    painter->save();

    if (hurt) painter->setOpacity(0.4);
    if (state.empty())
        painter->drawPixmap(boundingRect().topLeft(), pic_normal);
    else {
        if (walk_phase)
            painter->drawPixmap(boundingRect().topLeft(), pic_walk1);
        else
            painter->drawPixmap(boundingRect().topLeft(), pic_walk2);
        walk_phase = !walk_phase;
    }
    if (showShape) {
        painter->save();
        painter->setPen(Qt::red);
        painter->drawPath(shape());
        painter->restore();
    }

    painter->restore();
}

QPainterPath Protagonist::shape() const {
    QPainterPath path;
    path.addEllipse(QPointF(111 / 2, 210 / 2), 20, 20);
    return path;
}

void Protagonist::advance(int phase) {
    if (!phase || state.empty()) return;
    QPointF topUp = pos();
    QPointF buttonRight(topUp.x() + boundingRect().width(),
                        topUp.y() + boundingRect().height());

    QRectF sceneGeometry = scene()->sceneRect();

    // I am crazy
    const qreal MOVEY = 4.5, MOVEX = 6;
    if (state.contains(Qt::Key_Up) && !state.contains(Qt::Key_Down) &&
        !state.contains(Qt::Key_Left) && !state.contains(Qt::Key_Right)) {
        if (topUp.y() >= MOVEY) moveBy(0, -MOVEY);
    } else if (!state.contains(Qt::Key_Up) && state.contains(Qt::Key_Down) &&
               !state.contains(Qt::Key_Left) &&
               !state.contains(Qt::Key_Right)) {
        if (buttonRight.y() + MOVEY <= sceneGeometry.height()) moveBy(0, MOVEY);
    } else if (!state.contains(Qt::Key_Up) && !state.contains(Qt::Key_Down) &&
               state.contains(Qt::Key_Left) && !state.contains(Qt::Key_Right)) {
        if (topUp.x() >= MOVEX) moveBy(-MOVEX, 0);
    } else if (!state.contains(Qt::Key_Up) && !state.contains(Qt::Key_Down) &&
               !state.contains(Qt::Key_Left) && state.contains(Qt::Key_Right)) {
        if (buttonRight.x() + MOVEX <= sceneGeometry.width()) moveBy(MOVEX, 0);
    } else {
        const qreal DMOVEX = (MOVEX * sqrt(2) / 2.0),
                    DMOVEY = (MOVEY * sqrt(2) / 2.0);
        if (state.contains(Qt::Key_Up) && !state.contains(Qt::Key_Down) &&
            state.contains(Qt::Key_Left) && !state.contains(Qt::Key_Right)) {
            if (topUp.y() >= DMOVEY && topUp.x() >= DMOVEX)
                moveBy(-DMOVEX, -DMOVEY);
        } else if (state.contains(Qt::Key_Up) &&
                   !state.contains(Qt::Key_Down) &&
                   !state.contains(Qt::Key_Left) &&
                   state.contains(Qt::Key_Right)) {
            if (topUp.y() >= DMOVEY &&
                buttonRight.x() + DMOVEX <= sceneGeometry.width())
                moveBy(DMOVEX, -DMOVEY);
        } else if (!state.contains(Qt::Key_Up) &&
                   state.contains(Qt::Key_Down) &&
                   state.contains(Qt::Key_Left) &&
                   !state.contains(Qt::Key_Right)) {
            if (buttonRight.y() + DMOVEY <= sceneGeometry.height() &&
                topUp.x() >= DMOVEX)
                moveBy(-DMOVEX, DMOVEY);
        } else if (!state.contains(Qt::Key_Up) &&
                   state.contains(Qt::Key_Down) &&
                   !state.contains(Qt::Key_Left) &&
                   state.contains(Qt::Key_Right)) {
            if (buttonRight.y() + DMOVEY <= sceneGeometry.height() &&
                buttonRight.x() + DMOVEX <= sceneGeometry.width())
                moveBy(DMOVEX, DMOVEY);
        }
    }
    // emit currentPos(topUp);
}

// set the move smoothly
void Protagonist::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down ||
        event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        state.insert(event->key());
    if (event->key() == Qt::Key_Z) {
        if (event->isAutoRepeat() || sword.isVisible()) return;
        emit attack();
    }
}

void Protagonist::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down ||
        event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        state.remove(event->key());
}

void Protagonist::setShowShape(bool show) { showShape = show; }
