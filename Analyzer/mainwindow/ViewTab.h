/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef VIEWTAB_H
#define VIEWTAB_H

#include <QWidget>

namespace analyzer {
  namespace gui {
    namespace display {
      class AnalyzerEdit;
    }
    class AnalyzerTab;
    class ViewTab : public QWidget
    {
    private:
      ViewTab() {}

    public:
      explicit ViewTab(AnalyzerTab * parent);
      virtual ~ViewTab();

    private:
      display::AnalyzerEdit * analyzerEdit;

      void setup();
    };
  }
}
#endif