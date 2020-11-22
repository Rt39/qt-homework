#include "bullet.h"
#include <QPainter>
Bullet::Bullet() {
    pic.load(":/entity/bullet/bullet");
    setTransformOriginPoint(50, 50);
}

QRectF Bullet::boundingRect() const { return QRectF(0, 0, 100, 100); }

void Bullet::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                   QWidget*) {
    painter->save();

    if (showShape) {
        painter->setPen(Qt::red);
        painter->drawPath(shape());
    }
    painter->drawPixmap(boundingRect().topLeft(), pic);

    painter->restore();
}

QPainterPath Bullet::shape() const {
    QPainterPath path;
    path.addEllipse(QPointF(100 / 2, 100 / 2), 100 / 2, 100 / 2);
    return path;
}
