#include "mainwindow\MainWindow.h"
#include <QtWidgets/QApplication>

#include <memory>

#include "application\IOActionsImpl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::unique_ptr<analyzer::app::IOActions> ioActions(new analyzer::app::IOActionsImpl());
    analyzer::gui::MainWindow w(ioActions.get());
    w.show();
    return a.exec();
}
