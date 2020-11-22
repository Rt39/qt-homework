#ifndef XVE_H
#define XVE_H

#include "entity.h"
#include <QGraphicsObject>
#include <QObject>
#include <QPixmap>

class Xve : public Entity {
    Q_OBJECT
public:
    Xve();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;

private:
    QPixmap pic_xve;
};
#endif // XVE_H
