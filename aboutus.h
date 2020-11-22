#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QWidget>

class Aboutus : public QWidget {
    Q_OBJECT
public:
    explicit Aboutus(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // ABOUTUS_H
