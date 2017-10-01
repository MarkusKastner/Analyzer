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
#include "display\maindisplay\AnalyzerEdit.h"
#include "ViewTab.h"

#include "AnalyzerTab.h"

#include "AnalyzerLib\interpreter\Interpreter.h"
#include "AnalyzerLib\interpreter\formatter\ASCIIFormatter.h"

namespace analyzer{
  namespace gui{

    MainWindow::MainWindow(base::AnalyzerBase & analyzerBase, QWidget *parent)
      : QMainWindow(parent), actions(), analyzerBase(analyzerBase), tabWidget(nullptr),
      analyzeDock(nullptr), outputDock(nullptr), binaryDock(nullptr),
      documentStructure(nullptr), hexFile()
    {
      ui.setupUi(this);
      this->setup();
    }

    MainWindow::~MainWindow()
    {
      this->analyzerBase.UnregisterObserver(this);
    }

    void MainWindow::NotifyDocumentChange()
    {
      this->documentStructure->SetFiles(this->analyzerBase.GetFileNames());
      this->tabWidget->GetViewTab()->ClearFile();
    }

    void MainWindow::AddBinaryLine(const std::string & hex, const std::string & binary, const std::string & ascii, const std::string & numerical)
    {
      this->binaryDock->AddLine(hex, binary, ascii, numerical);
    }

    void MainWindow::ClearBinaryView()
    {
      this->binaryDock->Clear();
    }

    void MainWindow::AddOutputMessage(const std::string & message)
    {
      this->outputDock->AddMessage(message);
    }

    void MainWindow::SetAvailableAnalyzingOptions(const base::AnalyzingOptions & analyzingOptions)
    {
      this->analyzeDock->SetOptions(analyzingOptions);
    }

    void MainWindow::FileChange()
    {
      this->tabWidget->GetViewTab()->SetFile(this->analyzerBase.GetActiveAnalyzerFile());
    }

    void MainWindow::SetBinaryOutputFromString(const QString & binary)
    {
      this->binaryDock->Clear();
      this->binaryDock->SetBinaryOutputFromString(binary);
    }

    void MainWindow::SetBinaryOutputFromBytes(const std::vector<unsigned char> & data)
    {
      this->binaryDock->Clear();
      this->binaryDock->SetBinaryOutputFromBytes(data);
    }

    bool MainWindow::HasAnalyzeDock() const
    {
      return (this->analyzeDock != nullptr);
    }

    AnalyzeDock * MainWindow::GetAnalyzeDock() const
    {
      return this->analyzeDock;
    }

    base::AnalyzerBase & MainWindow::GetAnalyzerBase() const
    {
      return this->analyzerBase;
    }

    void MainWindow::setup()
    {
      this->analyzerBase.RegisterObserver(this);
      this->analyzerBase.SetApplicationDirectory(QApplication::applicationDirPath().toStdString());

      this->tabWidget = new AnalyzerTab(this);
      this->setCentralWidget(this->tabWidget);

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
      connect(this->ui.actionStart_Analyzing, &QAction::triggered, this->actions.get(), &Actions::OnStartAnalyzing);
      connect(this->ui.actionStop_Analyzing, &QAction::triggered, this->actions.get(), &Actions::OnStopAnalyzing);
      connect(this->ui.actionShow_as_Hex, &QAction::triggered, this, &MainWindow::onShowHex);
      connect(this->ui.actionDocumentStructure, &QAction::toggled, this, &MainWindow::onDocStructureToggled);
      connect(this->ui.actionOutput, &QAction::toggled, this, &MainWindow::onOutputToggled);
      connect(this->ui.actionAnalyze, &QAction::toggled, this, &MainWindow::onAnalyzeToggled);
      connect(this->ui.actionBinary_View, &QAction::toggled, this, &MainWindow::onBinViewToggled);
      connect(this->documentStructure, &DocumentStructure::visibilityChanged, this, &MainWindow::onDocViewVisibility);
      connect(this->outputDock, &DocumentStructure::visibilityChanged, this, &MainWindow::onOutputViewVisibility);
      connect(this->analyzeDock, &DocumentStructure::visibilityChanged, this, &MainWindow::onAnalyzeViewVisibility);
      connect(this->binaryDock, &DocumentStructure::visibilityChanged, this, &MainWindow::onBinaryViewVisibility);
      connect(this->documentStructure, &DocumentStructure::ActiveFileChanged, this, &MainWindow::activeFileChanged);
    }

    void MainWindow::activeFileChanged(const std::string & fileName)
    {
      this->analyzerBase.SetActiveFile(fileName);
    }

    void MainWindow::onDocStructureToggled(bool visible)
    {
      if (this->documentStructure->isHidden() && visible) {
        this->documentStructure->show();
      }
      else if (!this->documentStructure->isHidden() && !visible) {
        this->documentStructure->hide();
      }
    }

    void MainWindow::onOutputToggled(bool visible)
    {
      if (this->outputDock->isHidden() && visible) {
        this->outputDock->show();
      }
      else if (!this->outputDock->isHidden() && !visible) {
        this->outputDock->hide();
      }
    }

    void MainWindow::onAnalyzeToggled(bool visible)
    {
      if (this->analyzeDock->isHidden() && visible) {
        this->analyzeDock->show();
      }
      else if (!this->analyzeDock->isHidden() && !visible) {
        this->analyzeDock->hide();
      }
    }

    void MainWindow::onBinViewToggled(bool visible)
    {
      if (this->binaryDock->isHidden() && visible) {
        this->binaryDock->show();
      }
      else if (!this->binaryDock->isHidden() && !visible) {
        this->binaryDock->hide();
      }
    }

    void MainWindow::onDocViewVisibility(bool visible)
    {
      this->ui.actionDocumentStructure->setChecked(visible);
    }

    void MainWindow::onOutputViewVisibility(bool visible)
    {
      this->ui.actionOutput->setChecked(visible);
    }

    void MainWindow::onAnalyzeViewVisibility(bool visible)
    {
      this->ui.actionAnalyze->setChecked(visible);
    }

    void MainWindow::onBinaryViewVisibility(bool visible)
    {
      this->ui.actionBinary_View->setChecked(visible);
    }

    void MainWindow::onShowHex()
    {
      if (!this->analyzerBase.HasActivefile()) {
        return;
      }
      this->hexFile = this->analyzerBase.GetActiveAnalyzerFile()->CloneToHexFile();
      if (this->hexFile) {
        this->tabWidget->AddHexTab()->SetFile(this->hexFile.get());
      }
    }

    void MainWindow::assertAnalyzeDock()
    {
      if (this->analyzeDock == nullptr) {
        throw app::AppException("Invalid analyzerDock");
      }
    }
  }
}