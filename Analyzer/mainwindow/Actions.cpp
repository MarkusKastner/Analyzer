/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "Actions.h"

#include <QFileDialog>

#include "application\error\AppException.h"
#include "mainwindow\MainWindow.h"

namespace analyzer{
  namespace gui{
    Actions::Actions(MainWindow * mainWindow, base::AnalyzerBase & analyzerBase)
      :QObject(), mainWindow(mainWindow), analyzerBase(analyzerBase)
    {
      this->throwMainWindow();
    }

    Actions::~Actions()
    {

    }

    void Actions::OnOpen()
    {
      QString fileName(QFileDialog::getOpenFileName(this->mainWindow, tr("Read File")));
      this->analyzerBase.OpenDocument(fileName.toStdString());
    }

    void Actions::throwMainWindow()
    {
      if (nullptr == this->mainWindow){
        throw app::AppException("Invalid main window");
      }
    }
  }
}