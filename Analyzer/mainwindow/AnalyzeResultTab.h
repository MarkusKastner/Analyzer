/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZERESULTTAB_H
#define ANALYZERESULTTAB_H

#include <QWidget>
#include <QTextEdit>

namespace analyzer {
  namespace gui {
    class AnalyzerTab;
    class AnalyzeResultTab : public QWidget
    {
    private:
      AnalyzeResultTab() {}
    public:
      explicit AnalyzeResultTab(AnalyzerTab * parent);
      virtual ~AnalyzeResultTab();

    private:
      QTextEdit * textEdit;
      void setup();

    };
  }
}
#endif