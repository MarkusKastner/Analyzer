/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFBROWSER_H
#define PDFBROWSER_H

#include <QTextEdit>

#include "Analyzer\display\maindisplay\ViewOutput.h"
#include "AnalyzerLib\core\File.h"

namespace analyzer {
  namespace interpreter {
    class Interpreter;
  }
  namespace gui {
    namespace display {
      class PDFBrowser : public ViewOutput, public QTextEdit
      {
      public:
        PDFBrowser(QWidget * parent = 0);
        virtual ~PDFBrowser();

        virtual void SetFile(core::File * file);
        virtual void ClearFile();

      protected:
        virtual void mousePressEvent(QMouseEvent * evt);

      private:
        core::File * file;

      };
    }
  }
}
#endif