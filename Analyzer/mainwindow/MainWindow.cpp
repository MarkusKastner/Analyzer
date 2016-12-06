#include "MainWindow.h"

#include <QLayout>

#include "application\error\AppException.h"
#include "application\IOActions.h"

#include "AnalyzerLib\interpreter\Interpreter.h"

namespace analyzer{
  namespace gui{

    MainWindow::MainWindow(app::IOActions * ioActions, base::AnalyzerBase & analyzerBase, QWidget *parent)
      : QMainWindow(parent), actions(), ioActions(ioActions), analyzerBase(analyzerBase), analyzerEdit(nullptr)
    {
      ui.setupUi(this);
      this->setup();
    }

    MainWindow::~MainWindow()
    {
      this->ioActions->UnregisterObserver(this);
      this->analyzerBase.UnregisterObserver(this);
    }

    void MainWindow::NotifyDataLoad()
    {
      this->analyzerBase.Interpreter()->ResetData(this->ioActions->GetData());
    }

    void MainWindow::NotifyInterprterChange()
    {
      this->analyzerEdit->SetInterpreter(this->analyzerBase.Interpreter());
    }

    void MainWindow::setup()
    {
      this->throwIOActions();
      this->ioActions->RegisterObserver(this);
      this->analyzerBase.RegisterObserver(this);

      this->ui.centralWidget->setLayout(new QVBoxLayout());
      this->analyzerEdit = new gui::display::AnalyzerEdit();
      this->ui.centralWidget->layout()->addWidget(this->analyzerEdit);

      this->analyzerEdit->SetInterpreter(this->analyzerBase.Interpreter());
      
      this->actions.reset(new Actions(this, this->ioActions, this->analyzerBase));
      this->connectUI();
    }

    void MainWindow::connectUI()
    {
      connect(this->ui.actionOpen, &QAction::triggered, this->actions.get(), &Actions::OnOpen);
      connect(this->ui.actionBinary, &QAction::triggered, this->actions.get(), &Actions::OnWorkingModeBianry);
      connect(this->ui.actionText, &QAction::triggered, this->actions.get(), &Actions::OnWorkingModeText);
    }

    void MainWindow::throwIOActions()
    {
      if (nullptr == this->ioActions){
        throw app::AppException("Invalid io actions");
      }
    }
  }
}