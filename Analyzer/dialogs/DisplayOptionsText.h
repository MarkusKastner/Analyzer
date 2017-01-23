/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DISPLAYOPTIONSTEXT_H
#define DISPLAYOPTIONSTEXT_H

#include <QWidget>
#include <QRadioButton>

#include "AnalyzerLib\base\BaseData.h"

namespace analyzer{
  namespace gui{
    class DisplayOptionsText : public QWidget
    {
      Q_OBJECT
    public:
      DisplayOptionsText(QWidget * parent = 0);
      virtual ~DisplayOptionsText();

      base::DetailFormat GetFormat();

      void SetInterpreterOptions(const std::vector<base::DetailFormat> & options);

    signals:
      void DisplayOptionsChanged();

    private:
      QRadioButton * plainText;
      QRadioButton * xmlMode;
      QRadioButton * pdfMode;

      void setup();
      void onOptionsChange();
    };
  }
}
#endif