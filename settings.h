#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QWidget>
QT_BEGIN_NAMESPACE
class QSlider;
class QLabel;
class QSettings;
QT_END_NAMESPACE
class ChoiceButton;
class PushButton;
class Settings : public QWidget {
    Q_OBJECT
    friend class MainWindow;
    friend class GameControl;

public:
    explicit Settings(QWidget* parent = nullptr);

private:
    QSettings* remark;

    ChoiceButton *normal, *fullscreen;
    ChoiceButton *showShape, *noShowShape;
    QLabel* vol;
    QSlider* volume;
    PushButton *cancel, *confirm;

    bool hasChanged = false;
};

#endif // SETTINGS_H
