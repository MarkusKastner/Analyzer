#include "MainWindow.h"

#include <QLayout>

#include "application\error\AppException.h"
#include "dialogs\DisplayOptionsBinary.h"
#include "dialogs\DisplayOptionsText.h"
#include "dialogs\DocumentStructure.h"

#include "AnalyzerLib\interpreter\Interpreter.h"

namespace analyzer{
  namespace gui{

    MainWindow::MainWindow(base::AnalyzerBase & analyzerBase, QWidget *parent)
      : QMainWindow(parent), actions(), analyzerBase(analyzerBase), analyzerEdit(nullptr), 
      displayOptions(nullptr), documentStructure(nullptr)
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
      this->changeWorkingMode();
    }

    void MainWindow::NotifyFileChange()
    {
      this->documentStructure->SetFiles(this->analyzerBase.GetFileNames());
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
      this->displayOptions = new QDockWidget(tr("display options"), this);
      this->displayOptions->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
      DisplayOptions * options = nullptr;
      if (this->analyzerBase.GetWorkingMode() == analyzer::base::AnalyzerBase::WorkingMode::Binary){
        options = new DisplayOptionsBinary(this->displayOptions);
      }
      else{
        options = new DisplayOptionsText(this->displayOptions);
      }
       
      this->displayOptions->setWidget(options);
      this->addDockWidget(Qt::RightDockWidgetArea, this->displayOptions);

      this->documentStructure = new DocumentStructure(tr("document structure"), this);
      this->addDockWidget(Qt::LeftDockWidgetArea, this->documentStructure);
    }

    void MainWindow::changeWorkingMode()
    {
      DisplayOptions * options = nullptr;
      if (this->analyzerBase.GetWorkingMode() == analyzer::base::AnalyzerBase::WorkingMode::Binary){
        options = new DisplayOptionsBinary(this->displayOptions);
      }
      else{
        options = new DisplayOptionsText(this->displayOptions);
      }
      this->displayOptions->setWidget(options);
    }

    void MainWindow::connectUI()
    {
      connect(this->ui.actionOpen, &QAction::triggered, this->actions.get(), &Actions::OnOpen);
      connect(this->ui.actionBinary, &QAction::triggered, this->actions.get(), &Actions::OnWorkingModeBianry);
      connect(this->ui.actionText, &QAction::triggered, this->actions.get(), &Actions::OnWorkingModeText);
    }
  }
}