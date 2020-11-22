#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>
class GameView : public QGraphicsView {
    Q_OBJECT
    friend class GameControl;

public:
    GameView(QGraphicsScene* scene, QWidget* parent = nullptr);
    QSize sizeHint() const override;

protected:
    //    void mousePressEvent(QMouseEvent* event) override;
};

#endif // GAMEVIEW_H
