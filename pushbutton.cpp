#include "pushbutton.h"
#include <QImage>
PushButton::PushButton(const QString& normal, const QString& triggered,
                       QWidget* parent)
    : QPushButton(parent) {
    QImage a(normal);
    setStyleSheet(
        QString("QPushButton "
                "{border-image:url(%1);min-width:%2;max-width:%2;min-height:%3;"
                "max-width:%3;}")
            .arg(normal)
            .arg(a.width())
            .arg(a.height()) +
        QString("QPushButton:hover {border-image:url(%1);}").arg(triggered) +
        QString("QPushButton:pressed {border-image: url(%1);}").arg(triggered));
}
