#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
QT_BEGIN_NAMESPACE
class QLabel;
class QGroupBox;
class QVBoxLayout;
QT_END_NAMESPACE
class PushButton;

class Welcome : public QWidget {
    Q_OBJECT
    friend class GameControl;

public:
    explicit Welcome(QWidget* parent = nullptr);

private:
    QGroupBox* buttGroup;
    QVBoxLayout *buttLayout, *layout;
    QLabel* title;
    PushButton *new_game, *settings, *exit;

signals:
};

#endif // WELCOME_H
