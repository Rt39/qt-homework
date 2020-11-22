#include "xve.h"
#include <QPainter>
Xve::Xve() { pic_xve.load(":/entity/xve/xve"); }

QRectF Xve::boundingRect() const { return QRectF(0, 0, 141, 140); }

void Xve::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->save();

    if (showShape) {
        painter->setPen(Qt::red);
        painter->drawPath(shape());
    }
    painter->drawPixmap(boundingRect().topLeft(), pic_xve);

    painter->restore();
}
