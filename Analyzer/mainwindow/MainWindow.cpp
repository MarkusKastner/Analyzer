#include "MainWindow.h"

namespace analyzer{
  namespace gui{
    MainWindow::MainWindow(QWidget *parent)
      : QWidget(parent)
    {
      ui.setupUi(this);
    }

    MainWindow::~MainWindow()
    {

    }
  }
}