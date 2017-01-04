#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>

#include "AnalyzerLib\base\AnalyzerBase.h"

namespace analyzer{
  namespace gui{
    class MainWindow;
    class Actions : public QObject
    {
      Q_OBJECT
    public:
      Actions(MainWindow * mainWindow, base::AnalyzerBase & analyzerBase);
      virtual ~Actions();

      void OnOpen();

    private:
      MainWindow * mainWindow;
      base::AnalyzerBase & analyzerBase;

      void throwMainWindow();
    };
  }
}
#endif