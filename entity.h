#ifndef ENTITY_H
#define ENTITY_H
#include <QGraphicsObject>
class Entity : public QGraphicsObject {
    Q_OBJECT
    friend class GameControl;

protected:
    bool showShape;
};

#endif // ENTITY_H
