#include "sword.h"
#include <QPainter>
Sword::Sword() { pic.load(":/entity/sword/sword"); }

QRectF Sword::boundingRect() const { return QRectF(0, 0, 38, 137); }

void Sword::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                  QWidget*) {
    painter->save();

    if (showShape) {
        painter->save();
        painter->drawPath(shape());
        painter->restore();
    }
    painter->drawPixmap(boundingRect().topLeft(), pic);

    painter->restore();
}

QPainterPath Sword::shape() const {
    QPainterPath path;
    path.addRect(1, 1, 37, 136);
    return path;
}
