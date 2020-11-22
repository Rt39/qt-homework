#ifndef PROTAGONIST_H
#define PROTAGONIST_H

#include "entity.h"
#include "sword.h"
#include <QGraphicsObject>
#include <QObject>
#include <QPixmap>
#include <QSet>
class Protagonist : public Entity {
    Q_OBJECT
    friend class GameControl;

public:
    Protagonist();
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    QPainterPath shape() const override;
    void advance(int phase) override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QPixmap pic_normal, pic_walk1, pic_walk2;
    bool walk_phase = true;
    QSet<int> state;

    int blood = 100;
    int attackBlood = 100;
    bool hurt = false;

    Sword sword;

private slots:
    void setShowShape(bool show);

signals:
    void attack();
    /*things have not been realised*/
    //    void currentPos(QPointF);
    //    void gameOver();
};

#endif // PROTAGONIST_H
