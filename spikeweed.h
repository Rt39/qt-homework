#ifndef SPIKEWEED_H
#define SPIKEWEED_H

#include "entity.h"
#include <QGraphicsObject>
#include <QObject>
#include <QPixmap>
class Spikeweed : public Entity {
    Q_OBJECT
public:
    Spikeweed();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    QPainterPath shape() const override;

private:
    QPixmap pic_sp;
};

#endif // SPIKEWEED_H
