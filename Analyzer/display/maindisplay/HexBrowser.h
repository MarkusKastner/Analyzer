/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXBROWSER_H
#define HEXBROWSER_H

#include "ViewOutput.h"
#include <QTableWidget>

#include <vector>
#include <string>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\base\BaseData.h"

namespace analyzer {
  namespace interpreter {
    class HEXInterpreter;
  }
  namespace core {
    class File;
  }
  namespace gui {
    namespace display {
      class HexBrowser : public QTableWidget, public ViewOutput
      {
        Q_OBJECT
      public:
        HexBrowser(QWidget * parent = 0);
        virtual ~HexBrowser();

        virtual void SetFile(core::File * file);
        virtual void ClearFile();

        void AddHexRow(const std::vector<std::string> & hexExp);

      signals:
        void SetBinaryOutput(const std::vector<unsigned char> & data);

      private:
        core::File * file;

        void onSelection();
        void setup();
        interpreter::HEXInterpreter * getInterpreter();
      };
    }
  }
}
#endif
