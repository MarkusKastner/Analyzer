#include "MainWindow\Analyzer.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    analyzer::gui::Analyzer w;
    w.show();
    return a.exec();
}
