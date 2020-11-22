#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("混沌干不死");
    QCoreApplication::setApplicationName("monster battles");
    MainWindow w;
    w.show();
    return a.exec();
}
