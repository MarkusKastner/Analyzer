/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXTABLEWIDGET_H
#define HEXTABLEWIDGET_H

#include "ViewOutput.h"
#include <QTableWidget>

#include <vector>
#include <string>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\base\BaseData.h"
#include "AnalyzerLib\interpreter\HEXInterpreter.h"

namespace analyzer {
  namespace interpreter {
    class HEXInterpreter;
  }
  namespace core {
    class File;
  }
  namespace gui {
    namespace display {
      class HexBrowser;
      class HexTableWidget : public QTableWidget, public ViewOutput
      {
        Q_OBJECT
      public:
        HexTableWidget(HexBrowser * parent);
        virtual ~HexTableWidget();

        virtual void SetFile(core::File * file);
        virtual void ClearFile();

        void AddHexRow(const interpreter::HEXInterpreter::HexRow & hexExp);

      private:
        core::File * file;
        HexBrowser * browser;

        void onSelection();
        void setup();
        void setDetailOutput(const std::vector<unsigned char> & bytes);
        interpreter::HEXInterpreter * getInterpreter();
      };
    }
  }
}
#endif
