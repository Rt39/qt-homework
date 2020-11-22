#include "assassin.h"
#include <QPainter>
Assassin::Assassin() {
    pic_1.load(":/entity/assassin/assassin_1");
    pic_2.load(":/entity/assassin/assassin_2");
}

QRectF Assassin::boundingRect() const { return QRectF(0, 0, 226, 201); }

void Assassin::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                     QWidget*) {
    painter->save();

    if (phase)
        painter->drawPixmap(boundingRect().topLeft(), pic_1);
    else
        painter->drawPixmap(boundingRect().topLeft(), pic_2);
    if (showShape) {
        painter->setPen(Qt::red);
        painter->drawPath(shape());
    }

    painter->restore();
}

QPainterPath Assassin::shape() const {
    QPainterPath path;
    path.addEllipse(QPointF(226 / 2, 201 / 2), 226 / 2, 201 / 2);
    return path;
}

void Assassin::switchPhase() { phase = !phase; }
