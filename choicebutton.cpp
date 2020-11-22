#include "choicebutton.h"
#include <QImage>

ChoiceButton::ChoiceButton(const QString& normal, const QString& triggered,
                           QWidget* parent)
    : QRadioButton(parent) {
    QImage a(normal);
    setStyleSheet(
        QString("QRadioButton{min-width:%1;max-width:%1;min-height:%2;max-"
                "height:%2;}")
            .arg(a.width())
            .arg(a.height()) +
        QString("QRadioButton::indicator:checked {image:url(%1);}")
            .arg(triggered) +
        QString("QRadioButton::indicator:unchecked {image:url(%1);}")
            .arg(normal) +
        QString("QRadioButton::indicator:unchecked:hover {image: url(%1);}")
            .arg(triggered));
}
