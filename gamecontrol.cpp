#include "gamecontrol.h"
#include "assassin.h"
#include "bullet.h"
#include "choicebutton.h"
#include "gameview.h"
#include "nenecchi.h"
#include "protagonist.h"
#include "pushbutton.h"
#include "settings.h"
#include "spikeweed.h"
#include "welcome.h"
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QLabel>
#include <QMessageBox>
#include <QPalette>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QSettings>
#include <QSlider>
#include <QSoundEffect>
#include <QTimer>
#include <QVBoxLayout>
GameControl::GameControl(QObject* parent)
    : QObject(parent), scene(new QGraphicsScene), view(new GameView(scene)),
      clock(new QTimer), nene_clock(new QTimer), assassin_clock(new QTimer),
      settings(new Settings), bgm(new QSoundEffect) {

    clock->setInterval(20);
    nene_clock->setInterval(3000);
    assassin_clock->setInterval(5000);

    setScene();
    setBgm(":/background/titlebgm");
}

void GameControl::setScene() {
    setWelcome();
    setSettings();
}

void GameControl::setWelcome() {
    welcome = new Welcome;
    QGraphicsProxyWidget* t = scene->addWidget(welcome);

    const QRectF availableGeometry = view->sceneRect();
    t->resize(availableGeometry.width(), availableGeometry.height());
    t->setPos(availableGeometry.x(), availableGeometry.y());

    welcome->buttLayout->setAlignment(Qt::AlignHCenter);
    welcome->layout->setAlignment(Qt::AlignHCenter);
    QPalette pal = welcome->palette();
    pal.setBrush(QPalette::Background,
                 QBrush(QPixmap(":/background/yuki")
                            .scaled(availableGeometry.width(),
                                    availableGeometry.height())));
    welcome->setPalette(pal);

    QObject::connect(welcome->new_game, &PushButton::clicked, this,
                     &GameControl::newGame);
    QObject::connect(welcome->settings, &PushButton::clicked, this,
                     &GameControl::showSettings);
    QObject::connect(welcome->exit, &PushButton::clicked, &QApplication::exit);
}

void GameControl::setSettings() {
    settings = new Settings;
    set = scene->addWidget(settings);
    // set it on top of the scene
    set->setZValue(10);
    setSettingsPos();

    set->setVisible(false);

    QObject::connect(settings->fullscreen, &ChoiceButton::toggled, this,
                     &GameControl::resizeFullscreen);
    QObject::connect(settings->normal, &ChoiceButton::toggled, this,
                     &GameControl::resizeWindow);
    QObject::connect(settings->volume, &QSlider::valueChanged, this,
                     &GameControl::setVolume);
    QObject::connect(settings->showShape, &ChoiceButton::toggled, this,
                     &GameControl::showShape);
    QObject::connect(settings->noShowShape, &ChoiceButton::toggled, this,
                     &GameControl::noShowShape);

    QObject::connect(settings->confirm, &QPushButton::clicked, this,
                     &GameControl::changeSettings);
    QObject::connect(settings->cancel, &PushButton::clicked, this,
                     &GameControl::restoreSettings);
}

void GameControl::newGame() {
    if (!welcome) {
        if (QMessageBox::No ==
            QMessageBox::question(
                view, tr("新游戏"),
                tr("<font size=26 "
                   "face='华康少女文字W5-A'>真的要重新开始游戏吗？</"
                   "font>")))
            return;
        delete protangonist;
        delete nenecchi;
        nenecchi = nullptr;
        if (assassin) delete assassin;
        delete spikeweed;
    } else {
        welcome->setVisible(false);
        welcome->destroy();
        welcome = nullptr;
    }

    emit inGame(true);
    setBgm(":/background/gamebgm");

    // scene background
    const QRectF availableGeometry = view->sceneRect();
    scene->setBackgroundBrush(QBrush(
        QPixmap(":/background/gamebackground")
            .scaled(availableGeometry.width(), availableGeometry.height())));

    // protagonist
    protangonist = new Protagonist;
    scene->addItem(protangonist);
    protangonist->setPos(10, scene->height() / 3);
    protangonist->setFocus();
    const bool showShape = settings->remark->value("showShape").toBool();
    protangonist->showShape = showShape;

    // nenecchi
    nenecchi = new Nenecchi;
    scene->addItem(nenecchi);
    nenecchi->setPos(scene->width() / 7 * 5, scene->height() / 4);
    nenecchi->showShape = showShape;
    const int volume = settings->remark->value("volume").toInt();
    for (auto& s : nenecchi->sounds) {
        s->setVolume(volume);
    }
    QObject::connect(nene_clock, &QTimer::timeout, this, &GameControl::neneAct);
    ani_nene_group = new QSequentialAnimationGroup;
    /*QGraphicsObjects cannot set geometry*/
    //    QPropertyAnimation* ani_nene_up =
    //        new QPropertyAnimation(nenecchi, "geometry");
    QPropertyAnimation* ani_nene_up = new QPropertyAnimation(nenecchi, "pos");
    QPointF nenePos = nenecchi->pos();
    ani_nene_up->setDuration(1000);
    //    ani_nene_up->setStartValue(QRectF(nenePos.x(), nenePos.y(),
    //                                      nenecchi->boundingRect().width(),
    //                                      nenecchi->boundingRect().height()));
    //    ani_nene_up->setEndValue(QRectF(nenePos.x(), nenePos.y() - 100,
    //                                    nenecchi->boundingRect().width(),
    //                                    nenecchi->boundingRect().height()));
    ani_nene_up->setStartValue(nenePos);
    ani_nene_up->setEndValue(QPointF(nenePos.x(), nenePos.y() - 100));
    ani_nene_up->setEasingCurve(QEasingCurve::InOutCubic);
    //    QPropertyAnimation* ani_nene_down =
    //        new QPropertyAnimation(nenecchi, "geometry");
    QPropertyAnimation* ani_nene_down = new QPropertyAnimation(nenecchi, "pos");
    ani_nene_down->setDuration(1000);
    //    ani_nene_down->setStartValue(QRectF(nenePos.x(), nenePos.y() - 100,
    //                                        nenecchi->boundingRect().width(),
    //                                        nenecchi->boundingRect().height()));
    //    ani_nene_down->setEndValue(QRectF(nenePos.x(), nenePos.y(),
    //                                      nenecchi->boundingRect().width(),
    //                                      nenecchi->boundingRect().height()));
    ani_nene_down->setStartValue(QPointF(nenePos.x(), nenePos.y() - 100));
    ani_nene_down->setEndValue(nenePos);
    ani_nene_down->setEasingCurve(QEasingCurve::InOutCubic);
    ani_nene_group->addAnimation(ani_nene_up);
    ani_nene_group->addAnimation(ani_nene_down);
    ani_nene_group->setLoopCount(-1);
    ani_nene_group->start();

    // assain
    QObject::connect(assassin_clock, &QTimer::timeout, this,
                     &GameControl::emergeAssassin);
    assassin_clock->start();

    // spikeweed
    spikeweed = new Spikeweed;
    spikeweed->showShape = showShape;
    scene->addItem(spikeweed);
    spikeweed->setPos(scene->width() / 3, scene->height() / 3);

    // sword
    ani_sword = new QPropertyAnimation(&protangonist->sword, "rotation");
    ani_sword->setDuration(500);
    ani_sword->setKeyValueAt(0, 0);
    ani_sword->setKeyValueAt(0.5, 90);
    ani_sword->setKeyValueAt(1, 0);
    ani_sword->setLoopCount(1);

    QObject::connect(ani_sword, &QPropertyAnimation::finished,
                     [this]() { protangonist->sword.setVisible(false); });
    QObject::connect(protangonist, &Protagonist::attack, this,
                     &GameControl::attack);
    QObject::connect(clock, &QTimer::timeout, this, &GameControl::clockThings);
    play();
}

void GameControl::reToTitle() {
    if (QMessageBox::No ==
        QMessageBox::question(
            view, tr("返回标题画面"),
            tr("<font size=26 "
               "face='华康少女文字W5-A'>真的要返回标题画面吗？</"
               "font>")))
        return;
    emit inGame(false);
    setWelcome();
    setBgm(":/background/titlebgm");
}

void GameControl::showShape(bool toggled) {
    if (!toggled || !protangonist) return;
    protangonist->showShape = true;
    protangonist->sword.showShape = true;
    nenecchi->showShape = true;
    spikeweed->showShape = true;
    for (auto b : nenecchi->bullets) {
        if (*b) (*b)->showShape = true;
    }
    if (assassin) assassin->showShape = true;
    scene->update(scene->sceneRect());
}

void GameControl::noShowShape(bool toggled) {
    if (!toggled || !protangonist) return;
    protangonist->showShape = false;
    protangonist->sword.showShape = false;
    nenecchi->showShape = false;
    spikeweed->showShape = false;
    for (auto b : nenecchi->bullets) {
        if (*b) (*b)->showShape = false;
    }
    if (assassin) assassin->showShape = false;
    scene->update(scene->sceneRect());
}

void GameControl::attack() {
    protangonist->sword.setVisible(true);
    ani_sword->start();
}

void GameControl::clockThings() {
    scene->advance();
    protangonist->setFocus();
    crushThings();
}

void GameControl::crushThings() {
    if (protangonist->sword.isVisible() && nenecchi->phase != Nenecchi::Hurt &&
        nenecchi->phase != Nenecchi::Die &&
        protangonist->sword.collidesWithItem(nenecchi)) {
        nene_clock->start(3000);
        nenecchi->phase = Nenecchi::Hurt;
        nenecchi->son_hurt->play();
        nenecchi->blood -= protangonist->attackBlood;
        if (nenecchi->blood <= 0) {
            nenecchi->son_die->play();
            nenecchi->phase = Nenecchi::Die;
            ani_nene_group->stop();
            scene->update(scene->sceneRect());
        }
    }
    if (!protangonist->hurt) {
        for (auto b : nenecchi->bullets) {
            if (*b && protangonist->collidesWithItem(*b)) {
                protangonist->hurt = true;
                QTimer::singleShot(3000,
                                   [this]() { protangonist->hurt = false; });
            }
        }
        if (assassin && protangonist->collidesWithItem(assassin)) {
            protangonist->hurt = true;
            QTimer::singleShot(3000, [this]() { protangonist->hurt = false; });
        }
        if (spikeweed && protangonist->collidesWithItem(spikeweed)) {
            protangonist->hurt = true;
            QTimer::singleShot(3000, [this]() { protangonist->hurt = false; });
        }
    }
}

void GameControl::neneAct() {
    if (nenecchi->phase == Nenecchi::Die) return;
    if (nenecchi->phase == Nenecchi::Hurt)
        nenecchi->phase = Nenecchi::Attack;
    else if (nenecchi->phase == Nenecchi::Normal)
        nenecchi->phase = Nenecchi::Attack;
    else
        nenecchi->phase = Nenecchi::Normal;
    switch (nenecchi->phase) {
        case Nenecchi::Normal: {
            // nenecchi->phase = Nenecchi::Attack;
            break;
        }
        case Nenecchi::Attack: {
            nenecchi->son_attack->play();
            nenecchi->bullet1 = new Bullet;
            nenecchi->bullet2 = new Bullet;
            nenecchi->bullet3 = new Bullet;

            for (auto b : nenecchi->bullets) {
                const bool showShape =
                    settings->remark->value("showShape").toBool();
                (*b)->showShape = showShape;
            }

            QPointF attackPos = nenecchi->mapToScene(0, 300);
            scene->addItem(nenecchi->bullet1);
            scene->addItem(nenecchi->bullet2);
            scene->addItem(nenecchi->bullet3);
            nenecchi->bullet1->setPos(attackPos);
            nenecchi->bullet2->setPos(attackPos);
            nenecchi->bullet3->setPos(attackPos);
            const int DURATION = 200, TOTALDURATION = 2000;
            QParallelAnimationGroup* ani_bullet1_group =
                new QParallelAnimationGroup;
            QPropertyAnimation* ani_bullet1_rotate =
                new QPropertyAnimation(nenecchi->bullet1, "rotation");
            ani_bullet1_rotate->setDuration(DURATION);
            ani_bullet1_rotate->setStartValue(0);
            ani_bullet1_rotate->setEndValue(360);
            ani_bullet1_rotate->setLoopCount(TOTALDURATION / DURATION);
            QPropertyAnimation* ani_bullet1_move =
                new QPropertyAnimation(nenecchi->bullet1, "pos");
            ani_bullet1_move->setDuration(TOTALDURATION);
            ani_bullet1_move->setStartValue(attackPos);
            ani_bullet1_move->setEndValue(
                QPointF(attackPos.x() - 1000, attackPos.y()));
            ani_bullet1_move->setLoopCount(1);
            ani_bullet1_group->addAnimation(ani_bullet1_move);
            ani_bullet1_group->addAnimation(ani_bullet1_rotate);
            QParallelAnimationGroup* ani_bullet2_group =
                new QParallelAnimationGroup;
            QPropertyAnimation* ani_bullet2_rotate =
                new QPropertyAnimation(nenecchi->bullet2, "rotation");
            ani_bullet2_rotate->setDuration(DURATION);
            ani_bullet2_rotate->setStartValue(0);
            ani_bullet2_rotate->setEndValue(360);
            ani_bullet2_rotate->setLoopCount(TOTALDURATION / DURATION);
            QPropertyAnimation* ani_bullet2_move =
                new QPropertyAnimation(nenecchi->bullet2, "pos");
            ani_bullet2_move->setDuration(TOTALDURATION);
            ani_bullet2_move->setStartValue(attackPos);
            ani_bullet2_move->setEndValue(
                QPointF(attackPos.x() - 1000, attackPos.y() - 500));
            ani_bullet2_move->setLoopCount(1);
            ani_bullet2_group->addAnimation(ani_bullet2_move);
            ani_bullet2_group->addAnimation(ani_bullet2_rotate);
            QParallelAnimationGroup* ani_bullet3_group =
                new QParallelAnimationGroup;
            QPropertyAnimation* ani_bullet3_rotate =
                new QPropertyAnimation(nenecchi->bullet3, "rotation");
            ani_bullet3_rotate->setDuration(DURATION);
            ani_bullet3_rotate->setStartValue(0);
            ani_bullet3_rotate->setEndValue(360);
            ani_bullet3_rotate->setLoopCount(TOTALDURATION / DURATION);
            QPropertyAnimation* ani_bullet3_move =
                new QPropertyAnimation(nenecchi->bullet3, "pos");
            ani_bullet3_move->setDuration(TOTALDURATION);
            ani_bullet3_move->setStartValue(attackPos);
            ani_bullet3_move->setEndValue(
                QPointF(attackPos.x() - 1000, attackPos.y() + 500));
            ani_bullet3_move->setLoopCount(1);
            ani_bullet3_group->addAnimation(ani_bullet3_move);
            ani_bullet3_group->addAnimation(ani_bullet3_rotate);
            ani_bullet1_group->start(QAbstractAnimation::DeleteWhenStopped);
            ani_bullet2_group->start(QAbstractAnimation::DeleteWhenStopped);
            ani_bullet3_group->start(QAbstractAnimation::DeleteWhenStopped);
            QObject::connect(ani_bullet1_group,
                             &QParallelAnimationGroup::destroyed,
                             [this, &ani_bullet1_group]() mutable {
                                 nenecchi->bullet1->setVisible(false);
                                 delete nenecchi->bullet1;
                                 nenecchi->bullet1 = nullptr;
                                 ani_bullet1_group = nullptr;
                             });
            QObject::connect(ani_bullet2_group,
                             &QParallelAnimationGroup::destroyed,
                             [this, &ani_bullet2_group]() mutable {
                                 nenecchi->bullet2->setVisible(false);
                                 delete nenecchi->bullet2;
                                 nenecchi->bullet2 = nullptr;
                                 ani_bullet2_group = nullptr;
                             });
            QObject::connect(ani_bullet3_group,
                             &QParallelAnimationGroup::destroyed,
                             [this, &ani_bullet3_group]() mutable {
                                 nenecchi->bullet3->setVisible(false);
                                 delete nenecchi->bullet3;
                                 nenecchi->bullet3 = nullptr;
                                 ani_bullet3_group = nullptr;
                             });

            // nenecchi->phase = Nenecchi::Normal;
            break;
        }
        case Nenecchi::Hurt: {
            // things have done
            break;
        }
        case Nenecchi::Die: {
            // things have done
            break;
        }
    }
}

void GameControl::emergeAssassin() {
    assassin = new Assassin;

    const bool showShape = settings->remark->value("showShape").toBool();
    assassin->showShape = showShape;

    scene->addItem(assassin);
    assassin->setPos(scene->width() / 7 * 5, protangonist->pos().y());
    ani_assassin = new QPropertyAnimation(assassin, "pos");

    QTimer* assassin_phase = new QTimer(assassin);
    assassin_phase->setInterval(500);
    QObject::connect(assassin_phase, &QTimer::timeout, assassin,
                     &Assassin::switchPhase);
    ani_assassin->setDuration(4500);
    ani_assassin->setStartValue(assassin->pos());
    ani_assassin->setEndValue(
        QPointF(assassin->pos().x() - 1500, assassin->pos().y()));
    ani_assassin->setLoopCount(1);
    ani_assassin->start(QAbstractAnimation::DeleteWhenStopped);
    assassin_phase->start();
    QObject::connect(ani_assassin, &QPropertyAnimation::destroyed,
                     [&]() mutable {
                         if (assassin) assassin->setVisible(false);
                         delete assassin;
                         assassin = nullptr;
                         ani_assassin = nullptr;
                     });
}

// move settings to the centre of the view
void GameControl::setSettingsPos() {
    const QSizeF size = set->size();
    const QRectF availableGeometry = view->sceneRect();
    set->setPos((availableGeometry.width() - size.width()) / 2,
                (availableGeometry.height() - size.height()) / 2);
}

void GameControl::setBgm(const QString& file) {
    bgm->setSource(QUrl::fromLocalFile(file));
    bgm->setLoopCount(QSoundEffect::Infinite);

    bgm->play();
}

void GameControl::restoreSettings() {
    if (settings->hasChanged) {
        if (QMessageBox::Yes ==
            QMessageBox::question(
                view, tr("关闭"),
                tr("<font size=26 "
                   "face='华康少女文字W5-A'>设置已被改变，是否要抛弃设置？</"
                   "font>"))) {
            if (settings->remark->value("isFullscreen").toBool()) {
                settings->fullscreen->setChecked(true);
                settings->normal->setChecked(false);
                emit settings->fullscreen->toggled(true);
            } else {
                settings->fullscreen->setChecked(false);
                settings->normal->setChecked(true);
                emit settings->normal->toggled(true);
            }

            if (settings->remark->value("showShape").toBool()) {
                settings->showShape->setChecked(true);
                settings->noShowShape->setChecked(false);
                emit settings->showShape->toggled(true);
            } else {
                settings->showShape->setChecked(false);
                settings->noShowShape->setChecked(true);
                emit settings->noShowShape->toggled(true);
            }

            int vol = settings->remark->value("volume").toInt();
            settings->volume->setValue(vol);
            emit settings->volume->valueChanged(vol);
        } else
            return;
    }

    settings->hasChanged = false;

    hideSettings();
}

void GameControl::setVolume(int v) {
    settings->hasChanged = true;
    bgm->setVolume(static_cast<qreal>(v) / 100.0);
    if (nenecchi) {
        for (auto& s : nenecchi->sounds) {
            s->setVolume(static_cast<qreal>(v) / 100.0);
        }
    }
}

void GameControl::play() {
    clock->start();
    nene_clock->start();
    assassin_clock->start();
    ani_nene_group->start();
    if (ani_assassin) ani_assassin->start();
}

void GameControl::palse() {
    clock->stop();
    nene_clock->stop();
    assassin_clock->stop();
    if (ani_nene_group) ani_nene_group->stop();
    if (ani_assassin) ani_assassin->stop();
}

void GameControl::resizeFullscreen(bool toggled) {
    if (!toggled) return;
    settings->hasChanged = true;

    const QRect availableGeometry = QApplication::desktop()->screenGeometry();
    view->resize(availableGeometry.width(), availableGeometry.height());
    view->setSceneRect(availableGeometry);
    if (welcome) {
        welcome->resize(availableGeometry.width(), availableGeometry.height());
        QPalette pal = welcome->palette();
        pal.setBrush(QPalette::Background,
                     QBrush(QPixmap(":/background/yuki")
                                .scaled(availableGeometry.width(),
                                        availableGeometry.height())));
        welcome->setPalette(pal);
    } else {
        scene->setBackgroundBrush(
            QBrush(QPixmap(":/background/gamebackground")
                       .scaled(availableGeometry.width(),
                               availableGeometry.height())));
    }
    setSettingsPos();
}

void GameControl::resizeWindow(bool toggled) {
    if (!toggled) return;
    settings->hasChanged = true;

    const QSize availableGeometry = view->sizeHint();
    view->resize(availableGeometry);
    view->setSceneRect(0, 0, availableGeometry.width(),
                       availableGeometry.height());
    if (welcome) {
        welcome->resize(availableGeometry);
        QPalette pal = welcome->palette();
        pal.setBrush(QPalette::Background,
                     QBrush(QPixmap(":/background/yuki")
                                .scaled(availableGeometry.width(),
                                        availableGeometry.height())));
        welcome->setPalette(pal);
    } else {
        scene->setBackgroundBrush(
            QBrush(QPixmap(":/background/gamebackground")
                       .scaled(availableGeometry.width(),
                               availableGeometry.height())));
    }

    setSettingsPos();
}

void GameControl::showSettings() {
    emit notInSettings(false);
    palse();
    settings->setVisible(true);
    if (welcome) welcome->setVisible(false);
}

void GameControl::hideSettings() {
    emit notInSettings(true);
    settings->setVisible(false);
    if (welcome)
        welcome->setVisible(true);
    else
        play();
}

void GameControl::changeSettings() {
    const bool isFullscreen = settings->fullscreen->isChecked();
    settings->remark->setValue("isFullscreen", isFullscreen);

    const int volume = settings->volume->value();
    settings->remark->setValue("volume", volume);

    const bool showShape = settings->showShape->isChecked();
    settings->remark->setValue("showShape", showShape);

    settings->remark->sync();

    settings->hasChanged = false;

    hideSettings();
}
