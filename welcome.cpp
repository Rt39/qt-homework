#include "welcome.h"
#include "pushbutton.h"
#include <QGroupBox>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
Welcome::Welcome(QWidget* parent) : QWidget(parent) {
    setWindowFlag(Qt::FramelessWindowHint);
    title = new QLabel(this);
    title->setPixmap(QPixmap(":/widget/title"));

    buttGroup = new QGroupBox(this);
    buttGroup->setStyleSheet("border:none;");
    new_game = new PushButton(":/widget/newgameN", ":/widget/newgameT", this);
    settings = new PushButton(":/widget/settingsN", ":/widget/settingsT", this);
    exit = new PushButton(":/widget/exitN", ":/widget/exitT", this);
    buttLayout = new QVBoxLayout(buttGroup);
    buttLayout->addWidget(new_game);
    buttLayout->addWidget(settings);
    buttLayout->addWidget(exit);

    layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(buttGroup);
}
