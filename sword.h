#ifndef SWORD_H
#define SWORD_H

#include "entity.h"
#include <QGraphicsObject>
#include <QObject>
#include <QPixmap>
class Sword : public Entity {
    Q_OBJECT
    Q_PROPERTY(int rotation READ rotation WRITE setRotation) //旋转
    friend class GameControl;

public:
    Sword();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    QPainterPath shape() const override;

private:
    QPixmap pic;
};

#endif // SWORD_H
