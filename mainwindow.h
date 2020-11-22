#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamecontrol.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE
class Aboutus;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void readSettings();
    void creatActions();

    GameControl control;
    Aboutus* aboutus;

private slots:
    void setAboutus();
};
#endif // MAINWINDOW_H
