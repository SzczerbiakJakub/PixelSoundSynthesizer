#include "mainwindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Pixel Synth v. 1.0.0");
    w.show();
    return a.exec();
}