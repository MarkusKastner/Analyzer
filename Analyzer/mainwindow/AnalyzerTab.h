/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZERTAB_H
#define ANALYZERTAB_H

#include <QTabWidget>

class QTextEdit;
namespace analyzer {
  namespace gui {
    namespace display {
      class ViewOutput;
    }
    class ViewTab;
    class AnalyzeResultTab;

    class AnalyzerTab : public QTabWidget
    {
    private:
      AnalyzerTab() {}

    public:
      explicit AnalyzerTab(QWidget * parent = nullptr);
      virtual ~AnalyzerTab();

      ViewTab * GetViewTab();
      QTextEdit * GetResultTextEdit();

    private:
      ViewTab * viewTab;
      AnalyzeResultTab * resultTab;

      void setup();
    };
  }
}
#endif