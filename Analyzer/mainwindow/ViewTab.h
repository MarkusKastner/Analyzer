/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef VIEWTAB_H
#define VIEWTAB_H

#include <QWidget>

namespace analyzer {
  namespace core {
    class File;
  }
  namespace gui {
    namespace display {
      class ViewOutput;
    }
    class AnalyzerTab;
    class ViewTab : public QWidget
    {
      Q_OBJECT
    private:
      ViewTab() {}

    public:
      explicit ViewTab(AnalyzerTab * parent);
      virtual ~ViewTab();

      void SetFile(core::File * file);
      void ClearFile();

    private:
      display::ViewOutput * viewOutput;

      void setup();
    };
  }
}
#endif