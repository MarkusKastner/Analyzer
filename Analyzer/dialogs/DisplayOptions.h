#ifndef DISPLAYOPTIONS_H
#define DISPLAYOPTIONS_H

#include <QWidget>
#include <QRadioButton>

#include "DisplayOptionsBinary.h"
#include "DisplayOptionsText.h"

namespace analyzer{
  namespace gui{
    class DisplayOptions : public QWidget
    {
      Q_OBJECT
    public: 
      DisplayOptions(QWidget * parent = 0);
      virtual ~DisplayOptions();

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