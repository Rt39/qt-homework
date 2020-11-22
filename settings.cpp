#include "settings.h"
#include "choicebutton.h"
#include "pushbutton.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QPixmap>
#include <QSlider>
#include <QVBoxLayout>
Settings::Settings(QWidget* parent) : QWidget(parent) {
    setWindowFlag(Qt::FramelessWindowHint);
    QPalette pal = palette();
    pal.setBrush(QPalette::Background,
                 QBrush(QPixmap(":/background/settingsbg")));
    setPalette(pal);
    // setStyleSheet("QGroupBox{border:none;}");

    QGroupBox* windowSet = new QGroupBox(tr("窗口"), this);
    windowSet->setStyleSheet(
        "color:navy;font-family:华康少女文字W5-A;font-size:25px;");
    normal = new ChoiceButton(":/widget/windowN", ":/widget/windowT", this);
    fullscreen =
        new ChoiceButton(":/widget/fullscreanN", ":/widget/fullscreanT", this);
    QHBoxLayout* windowLayout = new QHBoxLayout(windowSet);
    windowLayout->addWidget(normal);
    windowLayout->addWidget(fullscreen);
    normal->setChecked(true);

    QGroupBox* shapeSet = new QGroupBox(tr("显示碰撞区域"), this);
    shapeSet->setStyleSheet(
        "color:navy;font-family:华康少女文字W5-A;font-size:25px;");
    showShape = new ChoiceButton(":/widget/showN", ":/widget/showT", this);
    noShowShape =
        new ChoiceButton(":/widget/noshowN", ":/widget/noshowT", this);
    QHBoxLayout* shapeLayout = new QHBoxLayout(shapeSet);
    shapeLayout->addWidget(showShape);
    shapeLayout->addWidget(noShowShape);
    noShowShape->setChecked(true);

    QGroupBox* volumeSet = new QGroupBox(this);
    QHBoxLayout* vollayout = new QHBoxLayout(volumeSet);
    vol = new QLabel(tr("音量"), this);
    vol->setStyleSheet(
        "color:navy;font-family:华康少女文字W5-A;font-size:25px;");

    vollayout->addWidget(vol);
    volume = new QSlider(this);
    volume->setOrientation(Qt::Horizontal);
    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(80);
    vollayout->addWidget(volume);

    QGroupBox* confirmSet = new QGroupBox(this);
    QHBoxLayout* conlayout = new QHBoxLayout(confirmSet);
    cancel = new PushButton(":/widget/cancelN", ":/widget/cancelT", this);
    confirm = new PushButton(":/widget/confirmN", ":/widget/confirmT", this);

    conlayout->addWidget(confirm);
    conlayout->addWidget(cancel);

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addWidget(windowSet);
    vlayout->addWidget(shapeSet);
    vlayout->addWidget(volumeSet);
    vlayout->addWidget(confirmSet);
}
