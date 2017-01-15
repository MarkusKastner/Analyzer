/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "mainwindow\MainWindow.h"
#include <QtWidgets/QApplication>

#include <memory>

#include "AnalyzerLib\base\AnalyzerBase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::unique_ptr<analyzer::base::AnalyzerBase> analyzerBase(new analyzer::base::AnalyzerBase());
    analyzer::gui::MainWindow w(*analyzerBase.get());
    w.show();
    return a.exec();
}
