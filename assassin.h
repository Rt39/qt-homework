#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "entity.h"
#include <QGraphicsObject>
#include <QObject>
#include <QPixmap>
class Assassin : public Entity {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    friend class GameControl;

public:
    Assassin();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    QPainterPath shape() const override;

public slots:
    void switchPhase();

private:
    QPixmap pic_1;
    QPixmap pic_2;

    bool phase = false;
};

#endif // ASSASSIN_H
