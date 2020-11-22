#include "mainwindow.h"
#include "aboutus.h"
#include "choicebutton.h"
#include "gameview.h"
#include "settings.h"
#include "welcome.h"
#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QGraphicsScene>
#include <QMenu>
#include <QMenuBar>
#include <QScreen>
#include <QSettings>
#include <QSlider>
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

    creatActions();

    // delete the MaximizeButton
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setCentralWidget(control.view);

    // move the MainWindow to screen Centre
    const QRect availableGeometry = screen()->availableGeometry();
    adjustSize();
    move((availableGeometry.width() - width()) / 2,
         (availableGeometry.height() - height()) / 2);
    setFixedSize(width(), height());

    QObject::connect(control.settings->fullscreen, &ChoiceButton::toggled,
                     [this](bool toggled) {
                         if (!toggled)
                             return;
                         else
                             showFullScreen();
                     });
    QObject::connect(control.settings->normal, &ChoiceButton::toggled,
                     [this](bool toggled) {
                         if (!toggled)
                             return;
                         else
                             showNormal();
                     });

    readSettings();
}

MainWindow::~MainWindow() {}

void MainWindow::readSettings() {
    if (!QFile::exists("./settings.ini")) {
        control.settings->remark =
            new QSettings("./settings.ini", QSettings::IniFormat);
        control.settings->remark->setValue("isFullscreen", false);
        control.settings->remark->setValue("volume", 80);
        control.settings->remark->sync();
        control.setVolume(80);
    } else {
        control.settings->remark =
            new QSettings("./settings.ini", QSettings::IniFormat);
        if (control.settings->remark->value("isFullscreen").toBool()) {
            control.settings->fullscreen->setChecked(true);
            control.settings->normal->setChecked(false);
            emit control.settings->fullscreen->toggled(true);
        }

        if (control.settings->remark->value("showShape").toBool()) {
            control.settings->showShape->setChecked(true);
            control.settings->noShowShape->setChecked(false);
            emit control.settings->showShape->toggled(true);
        }

        int vol = control.settings->remark->value("volume").toInt();
        control.settings->volume->setValue(vol);
        emit control.settings->volume->valueChanged(vol);
    }

    // first read settings to set the flag
    control.settings->hasChanged = false;
    control.settings->setVisible(false);
    control.welcome->setVisible(true);
    emit control.notInSettings(true);
}

void MainWindow::creatActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("文件(&F)"));

    QAction* new_gameAct =
        fileMenu->addAction(tr("&New game"), &control, &GameControl::newGame);
    new_gameAct->setShortcut(QKeySequence::New);
    QObject::connect(&control, &GameControl::notInSettings, new_gameAct,
                     &QAction::setEnabled);

    QAction* re_to_title = fileMenu->addAction(
        tr("返回至标题画面(&R)"), &control, &GameControl::reToTitle);
    re_to_title->setEnabled(false);
    QObject::connect(&control, &GameControl::inGame, re_to_title,
                     &QAction::setEnabled);

    fileMenu->addSeparator();

    QAction* exit = fileMenu->addAction(tr("退出游戏(&E)"));
    QObject::connect(exit, &QAction::triggered, &QApplication::exit);
    exit->setShortcut(QKeySequence::Quit);

    QMenu* setMenu = menuBar()->addMenu(tr("设置(&S)"));

    setMenu->addAction(tr("显示设置面板(&P)"), &control,
                       &GameControl::showSettings);

    setMenu->addSeparator();

    QActionGroup* windowGroup = new QActionGroup(this);
    windowGroup->setExclusive(true);
    QAction* window = windowGroup->addAction(tr("窗口(&W)"));
    QAction* fullscreen = windowGroup->addAction(tr("全屏(&F)"));
    window->setCheckable(true);
    fullscreen->setCheckable(true);
    window->setChecked(true);
    setMenu->addActions(windowGroup->actions());

    QObject::connect(window, &QAction::toggled, [this](bool toggeled) {
        if (!toggeled) return;
        control.showSettings();
        control.settings->normal->setChecked(true);
        control.settings->fullscreen->setChecked(false);
        emit control.settings->normal->toggled(true);
    });
    QObject::connect(fullscreen, &QAction::toggled, [this](bool toggeled) {
        if (!toggeled) return;
        control.showSettings();
        control.settings->fullscreen->setChecked(true);
        control.settings->normal->setChecked(false);
        emit control.settings->fullscreen->toggled(true);
    });
    QObject::connect(control.settings->normal, &ChoiceButton::toggled, window,
                     &QAction::setChecked);
    QObject::connect(control.settings->fullscreen, &ChoiceButton::toggled,
                     fullscreen, &QAction::setChecked);

    // setMenu->addSeparator();

    /*When the Action is checked, segmentation faults occurs. Why is it?*/

    //    QAction* showShape = setMenu->addAction(tr("显示判定区域"));
    //    showShape->setCheckable(true);
    //    showShape->setChecked(false);
    //    QObject::connect(showShape, &QAction::toggled, [this](bool toggled) {
    //        control.showSettings();
    //        control.settings->noShowShape->setChecked(!toggled);
    //        control.settings->showShape->setChecked(toggled);
    //        if (toggled)
    //            emit control.settings->showShape->toggled(true);
    //        else
    //            emit control.settings->noShowShape->toggled(true);
    //    });
    //    QObject::connect(control.settings->showShape, &ChoiceButton::toggled,
    //                     showShape, &QAction::setChecked);
    //    QObject::connect(control.settings->noShowShape,
    //    &ChoiceButton::toggled,
    //                     [showShape]() { showShape->setChecked(false); });

    QMenu* aboutMenu = menuBar()->addMenu(tr("帮助(&H)"));
    aboutMenu->addAction(tr("关于我们(&A)"), this, &MainWindow::setAboutus);
}

void MainWindow::setAboutus() {
    aboutus = new Aboutus(nullptr);
    aboutus->setFixedSize(800, 600);
    aboutus->adjustSize();
    const QRect availableGeometry = screen()->availableGeometry();
    aboutus->move((availableGeometry.width() - aboutus->width()) / 2,
                  (availableGeometry.height() - aboutus->height()) / 2);
    aboutus->setAttribute(Qt::WA_DeleteOnClose);
    aboutus->show();
}
