#include "MainWindow.h"

#include <QLayout>

#include "application\error\AppException.h"

#include "AnalyzerLib\interpreter\Interpreter.h"

namespace analyzer{
  namespace gui{

    MainWindow::MainWindow(base::AnalyzerBase & analyzerBase, QWidget *parent)
      : QMainWindow(parent), actions(), analyzerBase(analyzerBase), analyzerEdit(nullptr)
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
      this->analyzerEdit->SetInterpreter(this->analyzerBase.Interpreter());
    }

    void MainWindow::setup()
    {
      this->analyzerBase.RegisterObserver(this);

      this->ui.centralWidget->setLayout(new QVBoxLayout());
      this->analyzerEdit = new gui::display::AnalyzerEdit();
      this->ui.centralWidget->layout()->addWidget(this->analyzerEdit);

      this->analyzerEdit->SetInterpreter(this->analyzerBase.Interpreter());
      
      this->actions.reset(new Actions(this, this->analyzerBase));
      this->connectUI();
    }

    void MainWindow::connectUI()
    {
      connect(this->ui.actionOpen, &QAction::triggered, this->actions.get(), &Actions::OnOpen);
      connect(this->ui.actionBinary, &QAction::triggered, this->actions.get(), &Actions::OnWorkingModeBianry);
      connect(this->ui.actionText, &QAction::triggered, this->actions.get(), &Actions::OnWorkingModeText);
    }
  }
}