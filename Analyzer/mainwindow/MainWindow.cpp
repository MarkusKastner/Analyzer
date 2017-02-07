/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "MainWindow.h"

#include <QLayout>

#include "application\error\AppException.h"
#include "dialogs\DocumentStructure.h"
#include "dialogs\AnalyzeDock.h"
#include "dialogs\OutputDock.h"
#include "dialogs\BinaryDock.h"

#include "AnalyzerLib\interpreter\Interpreter.h"

namespace analyzer{
  namespace gui{

    MainWindow::MainWindow(base::AnalyzerBase & analyzerBase, QWidget *parent)
      : QMainWindow(parent), actions(), analyzerBase(analyzerBase), analyzerEdit(nullptr), 
      analyzeDock(nullptr), outputDock(nullptr), binaryDock(nullptr),
      documentStructure(nullptr)
    {
      ui.setupUi(this);
      this->setup();
    }

    MainWindow::~MainWindow()
    {
      this->analyzerBase.UnregisterObserver(this);
    }

    void MainWindow::NotifyInterprterChange()
    {
      this->analyzerEdit->SetFile(this->analyzerBase.GetActiveAnalyzerFile());
    }

    void MainWindow::NotifyDocumentChange()
    {
      this->documentStructure->SetFiles(this->analyzerBase.GetFileNames());
      this->analyzerEdit->ClearFile();
    }

    void MainWindow::DisplayOptionsChanged()
    {
    }

    void MainWindow::setup()
    {
      this->analyzerBase.RegisterObserver(this);

      this->analyzerEdit = new gui::display::AnalyzerEdit();
      this->setCentralWidget(this->analyzerEdit);
      
      this->setupDialogs();

      this->actions.reset(new Actions(this, this->analyzerBase));
      this->connectUI();
    }

    void MainWindow::setupDialogs()
    {
      this->analyzeDock = new AnalyzeDock(this);
      this->outputDock = new OutputDock(this);
      this->binaryDock = new BinaryDock(this);

      this->analyzeDock->setAllowedAreas(Qt::AllDockWidgetAreas);
      this->outputDock->setAllowedAreas(Qt::AllDockWidgetAreas);
      this->binaryDock->setAllowedAreas(Qt::AllDockWidgetAreas);

      this->addDockWidget(Qt::RightDockWidgetArea, this->analyzeDock);
      this->addDockWidget(Qt::BottomDockWidgetArea, this->outputDock);
      this->addDockWidget(Qt::BottomDockWidgetArea, this->binaryDock);

      this->documentStructure = new DocumentStructure(tr("document structure"), this);
      this->addDockWidget(Qt::LeftDockWidgetArea, this->documentStructure);
    }

    void MainWindow::connectUI()
    {
      connect(this->ui.actionOpen, &QAction::triggered, this->actions.get(), &Actions::OnOpen);
      connect(this->ui.actionClose, &QAction::triggered, this->actions.get(), &Actions::OnClose);
      connect(this->documentStructure, &DocumentStructure::ActiveFileChanged, this, &MainWindow::activeFileChanged);
    }

    void MainWindow::activeFileChanged(const std::string & fileName)
    {
      this->analyzerBase.SetActiveFile(fileName);
    }
  }
}