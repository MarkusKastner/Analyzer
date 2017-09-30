/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZEDOCK_H
#define ANALYZEDOCK_H

#include <QDockWidget>
#include "AnalyzerLib\base\AnalyzingOptions.h"

class QCheckBox;

namespace analyzer {
  namespace gui {
    class AnalyzeDock : public QDockWidget
    {
    public:
      AnalyzeDock(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
      virtual ~AnalyzeDock();

      void SetOptions(const base::AnalyzingOptions & analyzingOptions);
      void ResetOptions();

      bool CheckExtraordinary();
      bool CheckExecutable();
      bool CheckExternalLinks();
      bool CheckMacros();

    private:
      QCheckBox * extraordinary;
      QCheckBox * executable;
      QCheckBox * externalLinks;
      QCheckBox * macros;
      void setup();
    };
  }
}
#endif