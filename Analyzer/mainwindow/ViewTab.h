/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef VIEWTAB_H
#define VIEWTAB_H

#include <QWidget>

#include "AnalyzerLib/contentchecker/CheckObserver.h"
#include "AnalyzerLib/base/BaseData.h"

namespace analyzer {
  namespace core {
    class File;
  }
  namespace gui {
    namespace display {
      class ViewOutput;
    }
    class AnalyzerTab;
    class ViewTab : public QWidget, public checker::CheckObserver
    {
      Q_OBJECT
    private:
      ViewTab() {}

    public:
      explicit ViewTab(AnalyzerTab * parent);
      virtual ~ViewTab();

      void SetFile(core::File * file);
      void ClearFile();

      virtual void NotifyCheckRunFinished();
      virtual void NotifyCurrentIndex(const size_t & checkIndex);
      virtual void NotifyMarkedIndex(const size_t & markedIndex, const analyzer::base::AnalyzerRGB & color);

    private:
      display::ViewOutput * viewOutput;

      void setup();
    };
  }
}
#endif