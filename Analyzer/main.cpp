#include "mainwindow\MainWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    analyzer::gui::MainWindow w;
    w.show();
    return a.exec();
}
