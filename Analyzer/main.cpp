#include "Analyzer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Analyzer w;
    w.show();
    return a.exec();
}
