/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DISPLAYOPTIONS_H
#define DISPLAYOPTIONS_H

#include <QWidget>
#include <QRadioButton>

#include "DisplayOptionsBinary.h"
#include "DisplayOptionsText.h"

#include "AnalyzerLib\base\BaseData.h"

namespace analyzer{
  namespace core {
    class File;
  }
  namespace gui{
    class DisplayOptions : public QWidget
    {
      Q_OBJECT
    public: 
      DisplayOptions(QWidget * parent = 0);
      virtual ~DisplayOptions();

      base::BaseFormat GetBaseFormat();
      base::DetailFormat GetDetailedFormat();

      void SetFile(core::File * file);

    signals:
      void DisplayOptionsChanged();

    private:
      QRadioButton * textMode;
      QRadioButton * binaryMode;
      DisplayOptionsBinary * binaryOptions;
      DisplayOptionsText * textOptions;

      void setup();
      void onOptionsChange();

    };
  }
}
#endif