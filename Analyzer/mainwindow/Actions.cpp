/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "Actions.h"

#include <QFileDialog>
#include <QMessageBox>

#include "application/error/AppException.h"
#include "mainwindow/MainWindow.h"
#include "AnalyzerTab.h"
#include "AnalyzeResultTab.h"
#include "Analyzer/dialogs/AnalyzeDock.h"
#include "Analyzer/mainwindow/ViewTab.h"

#include "AnalyzerLib/contentchecker/ContentCheckerVault.h"

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
      QString fileName(QFileDialog::getOpenFileName(this->mainWindow, tr("Open Document"), this->analyzerBase.GetLastOpenDir().c_str()));
      if (!QFile(fileName).exists()) {
        return;
      }
      if (this->analyzerBase.HasData()) {
        this->analyzerBase.CloseDocument();
      }
      this->analyzerBase.OpenDocument(fileName.toStdString());
    }

    void Actions::OnClose()
    {
      this->analyzerBase.CloseDocument();
    }

    void Actions::OnStartAnalyzing()
    {
      if (!this->analyzerBase.HasActivefile() || !this->mainWindow->HasAnalyzeDock()) {
        return;
      }
      if (this->mainWindow->tabWidget->IsAnalyzeResultTabInitialized()) {
        this->mainWindow->tabWidget->GetAnalyzeResultTab()->Clear();
      }
      else {
        this->mainWindow->tabWidget->AddAnalyzeResultTab();
      }
      this->initCheckers();
    }

    void Actions::OnStopAnalyzing()
    {
    }

    void Actions::initCheckers()
    {
      try {
        if (!this->mainWindow->HasAnalyzeDock()) {
          return;
        }

        if (this->mainWindow->GetAnalyzeDock()->CheckExtraordinary()) {
          this->analyzerBase.GetContentCheckerVault().InitializeExtraordinaryChecker();
        }
        if (this->mainWindow->GetAnalyzeDock()->CheckExecutable()) {
          this->analyzerBase.GetContentCheckerVault().InitializeExecutableChecker();
        }
        if (this->mainWindow->GetAnalyzeDock()->CheckExternalLinks()) {
          this->analyzerBase.GetContentCheckerVault().InitializeExternalLinkChecker();
        }
        if (this->mainWindow->GetAnalyzeDock()->CheckMacros()) {
          this->analyzerBase.GetContentCheckerVault().InitializeMacroChecker();
        }

        if (this->mainWindow->tabWidget != nullptr && this->mainWindow->tabWidget->HasHexTab()) {
          this->analyzerBase.GetContentCheckerVault().RegisterCheckObserver(this->mainWindow->tabWidget->GetHexTab());
        }

        this->analyzerBase.GetContentCheckerVault().RunChecker();
      }
      catch (std::exception & ex) {
        QMessageBox::information(this->mainWindow, "Error", ex.what());
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