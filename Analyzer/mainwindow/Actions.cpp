#include "Actions.h"

#include <QFileDialog>

#include "application\IOActions.h"
#include "application\error\AppException.h"
#include "mainwindow\MainWindow.h"

namespace analyzer{
  namespace gui{
    Actions::Actions(MainWindow * mainWindow, app::IOActions * ioActions, base::AnalyzerBase & analyzerBase)
      :QObject(), mainWindow(mainWindow), ioActions(ioActions), analyzerBase(analyzerBase)
    {
      this->throwIOActions();
      this->throwMainWindow();
    }

    Actions::~Actions()
    {

    }

    void Actions::OnOpen()
    {
      QString fileName(QFileDialog::getOpenFileName(this->mainWindow, tr("Read File")));
      this->ioActions->ReadFile(fileName.toStdString());
    }
    
    void Actions::OnWorkingModeBianry()
    {
      this->analyzerBase.SetBinaryMode();
    }

    void Actions::OnWorkingModeText()
    {
      this->analyzerBase.SetTextMode();
    }

    void Actions::throwIOActions()
    {
      if (nullptr == this->ioActions){
        throw app::AppException("Invalid io actions");
      }
    }

    void Actions::throwMainWindow()
    {
      if (nullptr == this->mainWindow){
        throw app::AppException("Invalid main window");
      }
    }
  }
}