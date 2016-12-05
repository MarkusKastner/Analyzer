#include "MainWindow.h"

#include <QLayout>

#include "application\error\AppException.h"

#include "application\IOActions.h"

namespace analyzer{
  namespace gui{

    MainWindow::MainWindow(app::IOActions * ioActions, QWidget *parent)
      : QMainWindow(parent), actions(), ioActions(ioActions), analyzerEdit(nullptr)
    {
      ui.setupUi(this);
      this->setup();
    }

    MainWindow::~MainWindow()
    {

    }

    void MainWindow::setup()
    {
      this->throwIOActions();
      this->ui.centralWidget->setLayout(new QVBoxLayout());
      this->analyzerEdit = new gui::display::AnalyzerEdit();
      this->ui.centralWidget->layout()->addWidget(this->analyzerEdit);

      this->actions.reset(new Actions(this, this->ioActions));
      this->connectUI();
    }

    void MainWindow::connectUI()
    {
      connect(this->ui.actionOpen, &QAction::triggered, this->actions.get(), &Actions::OnOpen);
    }

    void MainWindow::throwIOActions()
    {
      if (nullptr == this->ioActions){
        throw app::AppException("Invalid io actions");
      }
    }
  }
}