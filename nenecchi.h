#ifndef NENECCHI_H
#define NENECCHI_H

#include "bullet.h"
#include "entity.h"
#include <QGraphicsObject>
#include <QList>
#include <QObject>
#include <QPixmap>
QT_BEGIN_NAMESPACE
class QSoundEffect;
QT_END_NAMESPACE
class Nenecchi : public Entity {
    Q_OBJECT
    /*it cannot be used*/
    // Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    friend class GameControl;

public:
    Nenecchi();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    //    void advance(int phase) override;
    QPainterPath shape() const override;

private:
    QPixmap pic_norm;
    QPixmap pic_attack;
    QPixmap pic_hurt;
    QPixmap pic_die;

    QList<QSoundEffect*> sounds;
    QSoundEffect* son_attack;
    QSoundEffect* son_hurt;
    QSoundEffect* son_die;

    int blood = 1000;

    QList<Bullet**> bullets; // pointer of pointer
    Bullet *bullet1 = nullptr, *bullet2 = nullptr, *bullet3 = nullptr;

    enum Phase { Normal, Attack, Hurt, Die } phase = Normal;
};

#endif // NENECCHI_H
