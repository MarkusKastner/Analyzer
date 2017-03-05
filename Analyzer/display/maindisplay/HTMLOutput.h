/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef HTMLOUTPUT_H
#define HTMLOUTPUT_H

#include "ViewOutput.h"

#include <QTextEdit>

#include "AnalyzerLib\core\File.h"
#include "AnalyzerLib\base\BaseData.h"

namespace analyzer {
  namespace core {
    class File;
  }
  namespace gui {
    namespace display {
      class HTMPOutput : public ViewOutput, public QTextEdit
      {
      public:
        HTMPOutput(QWidget * parent = 0);
        virtual ~HTMPOutput();

        virtual void SetFile(core::File * file);
        virtual void ClearFile();

      private:
        core::File * file;
      };
    }
  }
}
#endif