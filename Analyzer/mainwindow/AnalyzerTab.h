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

      ViewTab * AddHexTab();
      void ClearHexTab();

      bool IsAnalyzeResultTabInitialized() const;
      AnalyzeResultTab * GetAnalyzeResultTab() const;
      void AddAnalyzeResultTab();

    private:
      ViewTab * viewTab;
      AnalyzeResultTab * resultTab;
      ViewTab * hexTab;

      void setup();
      void onCloseTab(const int & index);

      void assertAnalyzeResultTab() const;
    };
  }
}
#endif