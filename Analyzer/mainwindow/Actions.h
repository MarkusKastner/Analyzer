#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>

#include "AnalyzerLib\base\AnalyzerBase.h"

namespace analyzer{
  namespace app{
    class IOActions;
  }
  namespace gui{
    class MainWindow;
    class Actions : public QObject
    {
      Q_OBJECT
    public:
      Actions(MainWindow * mainWindow, app::IOActions * ioActions, base::AnalyzerBase & analyzerBase);
      virtual ~Actions();

      void OnOpen();
      void OnWorkingModeBianry();
      void OnWorkingModeText();

    private:
      MainWindow * mainWindow;
      app::IOActions * ioActions;
      base::AnalyzerBase & analyzerBase;

      void throwIOActions();
      void throwMainWindow();
    };
  }
}
#endif