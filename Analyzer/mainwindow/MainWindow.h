#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

#include <memory>

#include "Actions.h"
#include "application\IOActionObserver.h"
#include "display\maindisplay\AnalyzerEdit.h"
#include "AnalyzerLib\base\AnalyzerBase.h"

namespace analyzer{
  namespace app{
    class IOActions;
  }
  namespace core{
    class ByteCollection;
  }
  namespace gui{

    class MainWindow : public QMainWindow, public app::IOActionObserver
    {
      Q_OBJECT

    public:
      MainWindow(app::IOActions * ioActions, base::AnalyzerBase & analyzerBase, QWidget *parent = 0);
      ~MainWindow();

      virtual void NotifyDataLoad();

    private:
      Ui::MainWindow ui;
      std::unique_ptr<Actions> actions;
      app::IOActions * ioActions;
      base::AnalyzerBase & analyzerBase;
      gui::display::AnalyzerEdit * analyzerEdit;

      void setup();
      void connectUI();

      void throwIOActions();
    };
  }
}
#endif 
