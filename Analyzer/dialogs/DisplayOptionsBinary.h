/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DISPLAYOPTIONSBINARY_H
#define DISPLAYOPTIONSBINARY_H

#include <QWidget>
#include <QRadioButton>

#include "AnalyzerLib\base\BaseData.h"

namespace analyzer{
  namespace gui{
    class DisplayOptionsBinary : public QWidget
    {
      Q_OBJECT
    public:
      DisplayOptionsBinary(QWidget * parent = 0);
      virtual ~DisplayOptionsBinary();

      base::DetailFormat GetFormat();

    signals:
      void DisplayOptionsChanged();

    private:
      QRadioButton * binary;
      QRadioButton * hex;

      void setup();
      void onOptionsChange();
    };
  }
}
#endif