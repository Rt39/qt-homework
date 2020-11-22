#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include <QGraphicsObject>
#include <QObject>
#include <QPixmap>
class Bullet : public Entity {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(int rotation READ rotation WRITE setRotation)
public:
    Bullet();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    QPainterPath shape() const override;

private:
    QPixmap pic;
};

#endif // BULLET_H
