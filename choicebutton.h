#ifndef CHOICEBUTTON_H
#define CHOICEBUTTON_H

#include <QObject>
#include <QRadioButton>
QT_BEGIN_NAMESPACE
class QEvent;
QT_END_NAMESPACE
class ChoiceButton : public QRadioButton {
    Q_OBJECT
public:
    ChoiceButton(const QString& normal, const QString& triggered,
                 QWidget* parent = nullptr);

protected:
};

#endif // CHOICEBUTTON_H
