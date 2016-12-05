#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

#include <memory>

#include "Actions.h"
#include "display\maindisplay\AnalyzerEdit.h"

namespace analyzer{
  namespace app{
    class IOActions;
  }
  namespace gui{

    class MainWindow : public QMainWindow
    {
      Q_OBJECT

    public:
      MainWindow(app::IOActions * ioActions, QWidget *parent = 0);
      ~MainWindow();

    private:
      Ui::MainWindow ui;
      std::unique_ptr<Actions> actions;
      app::IOActions * ioActions;
      gui::display::AnalyzerEdit * analyzerEdit;

      void setup();
      void connectUI();

      void throwIOActions();
    };
  }
}
#endif 
