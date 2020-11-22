#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QList>
#include <QObject>
QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsProxyWidget;
class QGraphicsObject;
class QTimer;
class QSoundEffect;
class QPropertyAnimation;
class QSequentialAnimationGroup;
QT_END_NAMESPACE
class MainWindow;
class GameView;
class Settings;
class Welcome;
class Protagonist;
class Nenecchi;
class Assassin;
class Spikeweed;

class GameControl : public QObject {
    Q_OBJECT
    friend class MainWindow;

public:
    explicit GameControl(QObject* parent = nullptr);
private slots:
    void play();
    void palse();

    void resizeFullscreen(bool toggled);
    void resizeWindow(bool toggled);
    void showShape(bool toggled);
    void noShowShape(bool toggled);
    void setVolume(int v);

    void showSettings();
    void hideSettings();
    void changeSettings();
    void restoreSettings();

    void newGame();
    void reToTitle();

    void clockThings();
    void crushThings();

    void neneAct();
    void emergeAssassin();
    void attack();

private:
    void setScene();
    void setWelcome();
    void setSettings();
    void setSettingsPos();
    void setBgm(const QString& file);

    QGraphicsScene* scene;
    GameView* view;
    QTimer *clock, *nene_clock, *assassin_clock;

    Settings* settings;
    Welcome* welcome;
    QGraphicsProxyWidget* set;
    QSoundEffect* bgm;

    Protagonist* protangonist = nullptr;
    Nenecchi* nenecchi = nullptr;
    Assassin* assassin = nullptr;
    Spikeweed* spikeweed = nullptr;

    QPropertyAnimation* ani_sword = nullptr;
    QPropertyAnimation* ani_assassin = nullptr;
    QSequentialAnimationGroup* ani_nene_group = nullptr;

signals:
    void inGame(bool in);
    void notInSettings(bool in);
};

#endif // GAMECONTROL_H
