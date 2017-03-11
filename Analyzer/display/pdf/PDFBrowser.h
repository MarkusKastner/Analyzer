/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef PDFBROWSER_H
#define PDFBROWSER_H

#include <QTextEdit>

namespace analyzer {
  namespace interpreter {
    class Interpreter;
  }
  namespace gui {
    namespace display {
      class PDFBrowser : public QTextEdit
      {
        Q_OBJECT
      public:
        PDFBrowser(QWindow * parent = 0);
        virtual ~PDFBrowser();

      signals:
        void OnClick(QMouseEvent * evt);

      protected:
        virtual void mousePressEvent(QMouseEvent * evt);

      };
    }
  }
}
#endif