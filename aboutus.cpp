#include "aboutus.h"
#include <QPainter>

Aboutus::Aboutus(QWidget* parent) : QWidget(parent) {
    resize(800, 600);
    setWindowTitle(tr("About us"));
}

// draw initial ui
void Aboutus::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);

    /*-----PART1 RULES-----*/
    QRect rect(50.0, 50.0, 700.0, 250.0);
    QPen pen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(rect);

    QFont title_font("Adobe Gothic Std B", 10, QFont::Bold, false);
    title_font.setLetterSpacing(QFont::AbsoluteSpacing, 5);
    painter.setFont(title_font);
    painter.drawText(330, 80, tr("GAME RULES"));

    QFont child_font1("Adobe Gothic Std B", 10, QFont::Normal, false);
    child_font1.setLetterSpacing(QFont::AbsoluteSpacing, 2);
    painter.setFont(child_font1);
    painter.drawText(120, 160, tr("----HOW TO MOVE"));
    QRect keys[ 4 ];
    keys[ 0 ] = QRect(530.0, 110.0, 35.0, 35.0);
    keys[ 1 ] = QRect(530.0, 150.0, 35.0, 35.0);
    keys[ 2 ] = QRect(490.0, 150.0, 35.0, 35.0);
    keys[ 3 ] = QRect(570.0, 150.0, 35.0, 35.0);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    for (short i = 0; i < 4; i++) {
        painter.drawRect(keys[ i ]);
    }
    painter.drawText(keys[ 0 ], Qt::AlignCenter, tr(" ↑ "));
    painter.drawText(keys[ 1 ], Qt::AlignCenter, tr(" ↓ "));
    painter.drawText(keys[ 2 ], Qt::AlignCenter, tr(" ← "));
    painter.drawText(keys[ 3 ], Qt::AlignCenter, tr(" → "));

    painter.drawText(120, 250, tr("----HOW TO ATTACK"));
    QRect key5(530.0, 220.0, 35.0, 35.0);
    painter.drawRect(key5);
    painter.drawText(key5, Qt::AlignCenter, tr(" Z"));

    /*-----PART2 STAFF-----*/
    QRect rect2(50.0, 320.0, 700.0, 85.0);
    pen.setStyle(Qt::DashDotLine);
    painter.setPen(pen);
    painter.drawRect(rect2);

    painter.setFont(title_font);
    painter.drawText(320, 350, tr("GROUP STAFF"));
    QFont child_font2("Adobe Gothic Std B", 10, QFont::Normal, false);
    child_font2.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    painter.setFont(child_font2);
    painter.drawText(65, 390, tr("Anonymous"));
    painter.drawText(240, 390, tr("Anonymous"));
    painter.drawText(405, 390, tr("Anonymous"));
    painter.drawText(580, 390, tr("Anonymous"));

    /*-----PART3 TOOLS & VERSION-----*/
    QRect rect3(50.0, 425.0, 700.0, 130.0);
    pen.setStyle(Qt::DashDotLine);
    painter.setPen(pen);
    painter.drawRect(rect3);

    painter.setFont(title_font);
    painter.drawText(295, 455, tr("TOOLS & VERSION"));
    painter.setFont(child_font1);
    painter.drawText(120, 495, tr("---TOOLS"));
    painter.drawText(120, 530, tr("---VERSION"));
    painter.setFont(child_font2);
    painter.drawText(500, 495, tr("POWERED BY Qt"));
    painter.drawText(500, 530, tr("v1.0.0"));
}
