/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "MainWindow.h"

#include <QLayout>

#include "application\error\AppException.h"
#include "dialogs\DisplayOptions.h"
#include "dialogs\DocumentStructure.h"

#include "AnalyzerLib\interpreter\Interpreter.h"

namespace analyzer{
  namespace gui{

    MainWindow::MainWindow(base::AnalyzerBase & analyzerBase, QWidget *parent)
      : QMainWindow(parent), actions(), analyzerBase(analyzerBase), analyzerEdit(nullptr), 
      displayOptionsDock(nullptr), documentStructure(nullptr), displayOptions(nullptr)
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

    void MainWindow::NotifyFileChange()
    {
      this->DisplayOptionsChanged();
      this->documentStructure->SetFiles(this->analyzerBase.GetFileNames());
    }

    void MainWindow::DisplayOptionsChanged()
    {
      this->analyzerBase.SetNewDisplayOptions(this->displayOptions->GetBaseFormat(), this->displayOptions->GetDetailedFormat());
      this->analyzerEdit->SetNewDisplayOptions(this->displayOptions->GetBaseFormat(), this->displayOptions->GetDetailedFormat());
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
      this->displayOptionsDock = new QDockWidget(tr("display options"), this);
      this->displayOptionsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

      this->displayOptions = new DisplayOptions(this->displayOptionsDock);
      this->displayOptionsDock->setWidget(this->displayOptions);
      this->addDockWidget(Qt::RightDockWidgetArea, this->displayOptionsDock);

      this->documentStructure = new DocumentStructure(tr("document structure"), this);
      this->addDockWidget(Qt::LeftDockWidgetArea, this->documentStructure);
    }

    void MainWindow::connectUI()
    {
      connect(this->ui.actionOpen, &QAction::triggered, this->actions.get(), &Actions::OnOpen);
      connect(this->documentStructure, &DocumentStructure::ActiveFileChanged, this, &MainWindow::activeFileChanged);
      connect(this->displayOptions, &DisplayOptions::DisplayOptionsChanged, this, &MainWindow::DisplayOptionsChanged);
    }

    void MainWindow::activeFileChanged(const std::string & fileName)
    {
      this->analyzerBase.SetActiveFile(fileName);
    }
  }
}