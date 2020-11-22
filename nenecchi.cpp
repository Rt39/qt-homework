#include "nenecchi.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QSoundEffect>
Nenecchi::Nenecchi()
    : son_attack(new QSoundEffect(this)), son_hurt(new QSoundEffect(this)),
      son_die(new QSoundEffect(this)) {
    pic_norm.load(":/entity/nenecchi/nene");
    pic_attack.load(":/entity/nenecchi/attack");
    pic_hurt.load(":/entity/nenecchi/hurt");
    pic_die.load(":/entity/nenecchi/die");

    son_attack->setSource(QUrl::fromLocalFile(":/entity/nenecchi/attacksound"));
    son_hurt->setSource(QUrl::fromLocalFile(":/entity/nenecchi/hurtsound"));
    son_die->setSource(QUrl::fromLocalFile(":/entity/nenecchi/diesound"));
    sounds << son_attack << son_hurt << son_die;
    for (auto& s : sounds)
        s->setLoopCount(1);

    bullets << &bullet1 << &bullet2 << &bullet3;
}

QRectF Nenecchi::boundingRect() const { return QRectF(0, 0, 360, 360); }

void Nenecchi::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                     QWidget*) {
    painter->save();

    switch (phase) {
        case Normal:
            painter->drawPixmap(boundingRect().topLeft(), pic_norm);
            break;
        case Attack:
            painter->drawPixmap(boundingRect().topLeft(), pic_attack);
            break;
        case Hurt:
            painter->setOpacity(0.4);
            painter->drawPixmap(boundingRect().topLeft(), pic_hurt);
            break;
        case Die:
            painter->drawPixmap(boundingRect().topLeft(), pic_die);
            break;
    }
    if (showShape) {
        painter->setPen(Qt::blue);
        painter->drawPath(shape());
    }

    painter->restore();
}

// void Nenecchi::advance(int phase) {
//    if (!phase) return;
//    QPointF topUp = pos();
//    QPointF buttonRight(topUp.x() + boundingRect().width(),
//                        topUp.y() + boundingRect().height());

//    QRectF sceneGeometry = scene()->sceneRect();

//    int rd = qrand() % 4;
//    const qreal MOVEY = 1, MOVEX = 1;
//    switch (rd) {
//        case 0:
//            if (topUp.y() >= MOVEY) moveBy(0, -MOVEY);
//            break;
//        case 1:
//            if (buttonRight.y() + MOVEY <= sceneGeometry.height())
//                moveBy(0, MOVEY);
//            break;
//        case 2:
//            if (topUp.x() >= MOVEX) moveBy(-MOVEX, 0);
//            break;
//        case 3:
//            if (buttonRight.x() + MOVEX <= sceneGeometry.width())
//                moveBy(MOVEX, 0);
//            break;
//    }
//}

QPainterPath Nenecchi::shape() const {
    QPainterPath path;
    path.addEllipse(QPointF(360 / 2, 360 / 2), 360 / 2, 360 / 2);
    return path;
}
