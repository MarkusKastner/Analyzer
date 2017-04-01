/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HEXBROWSER_H
#define HEXBROWSER_H

#include "ViewOutput.h"
#include <QWidget>
#include <QLineEdit>

#include <vector>
#include <string>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\base\BaseData.h"

class QTableWidget;
class QTableWidgetItem;

namespace analyzer {
  namespace interpreter {
    class HEXInterpreter;
  }
  namespace core {
    class File;
  }
  namespace gui {
    namespace display {
      class HexTableWidget;
      class HexBrowser : public QWidget, public ViewOutput
      {
        Q_OBJECT
      public:
        HexBrowser(QWidget * parent = 0);
        virtual ~HexBrowser();

        virtual void SetFile(core::File * file);
        virtual void ClearFile();

        void AddHexRow(const std::vector<std::string> & hexExp);

        void SetIntegerValue(const int & integerValue);
        void SetDoubleValue(const double & doubleValue);
        void SetWideCharacter(const wchar_t & wideCharacter);

        void ClearValues();

      signals:
        void SetBinaryOutput(const std::vector<unsigned char> & data);

      private:
        HexTableWidget * tableWidget;
        QTableWidget * castTable;

        QTableWidgetItem * integerCast;
        QTableWidgetItem * doubleCast;
        QTableWidgetItem * wideCharacter;

        core::File * file;

        void setup();
        void createCastTable();
      };
    }
  }
}
#endif
