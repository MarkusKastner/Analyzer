/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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
      void OnClose();
      void OnStartAnalyzing();
      void OnStopAnalyzing();

    private:
      MainWindow * mainWindow;
      base::AnalyzerBase & analyzerBase;

      void throwMainWindow();
    };
  }
}
#endif