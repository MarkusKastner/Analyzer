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
      //this->analyzerEdit->SetInterpreter(this->analyzerBase.Currentfile()->Interpreter());
      this->changeWorkingMode();
    }

    void MainWindow::NotifyFileChange()
    {

    }

    void MainWindow::setup()
    {
      this->analyzerBase.RegisterObserver(this);

      this->analyzerEdit = new gui::display::AnalyzerEdit();
      this->setCentralWidget(this->analyzerEdit);
      //this->analyzerEdit->SetInterpreter(this->analyzerBase.Currentfile()->Interpreter());
      
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

      this->documentStructure = new QDockWidget(tr("document structure"), this);
      this->documentStructure->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
      this->documentStructure->setWidget(new DocumentStructure());
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