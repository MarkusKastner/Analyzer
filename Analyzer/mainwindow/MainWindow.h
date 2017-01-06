#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

#include <memory>

#include <QDockWidget>

#include "Actions.h"
#include "display\maindisplay\AnalyzerEdit.h"
#include "AnalyzerLib\base\AnalyzerBase.h"
#include "AnalyzerLib\base\AnalyzerBaseObserver.h"

namespace analyzer{
  namespace gui{
    class DocumentStructure;
    class DisplayOptions;
    class MainWindow : public QMainWindow, public base::AnalyzerBaseObserver
    {
      Q_OBJECT

    public:
      MainWindow(base::AnalyzerBase & analyzerBase, QWidget *parent = 0);
      ~MainWindow();

      virtual void NotifyInterprterChange();
      virtual void NotifyFileChange();

      void DisplayOptionsChanged();

    private:
      Ui::MainWindow ui;
      std::unique_ptr<Actions> actions;
      base::AnalyzerBase & analyzerBase;
      gui::display::AnalyzerEdit * analyzerEdit;

      QDockWidget * displayOptionsDock;
      DocumentStructure * documentStructure;
      DisplayOptions * displayOptions;

      void setup();
      void setupDialogs();

      void connectUI();

      void activeFileChanged(const std::string & fileName);
    };
  }
}
#endif 
