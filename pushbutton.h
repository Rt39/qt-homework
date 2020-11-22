#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>
#include <QPushButton>
class PushButton : public QPushButton {
    Q_OBJECT
public:
    PushButton(const QString& normal, const QString& triggered,
               QWidget* parent = nullptr);
};

#endif // PUSHBUTTON_H
