#include "spikeweed.h"
#include <QPainter>
Spikeweed::Spikeweed() { pic_sp.load(":/entity/spikeweed/spikeweed"); }

QRectF Spikeweed::boundingRect() const { return QRectF(0, 0, 198, 104); }

void Spikeweed::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                      QWidget*) {
    painter->save();

    if (showShape) {
        painter->setPen(Qt::red);
        painter->drawPath(shape());
    }
    painter->drawPixmap(boundingRect().topLeft(), pic_sp);

    painter->restore();
}

QPainterPath Spikeweed::shape() const {
    QPainterPath path;
    path.addRect(1, 1, 197, 103);
    return path;
}
