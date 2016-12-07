#ifndef DISPLAYOPTIONSTEXT_H
#define DISPLAYOPTIONSTEXT_H

#include "DisplayOptions.h"

#include <QRadioButton>

namespace analyzer{
  namespace gui{
    class DisplayOptionsText : public DisplayOptions
    {
    public:
      DisplayOptionsText(QWidget * parent = 0);
      virtual ~DisplayOptionsText();

    private:
      QRadioButton * plainText;
      QRadioButton * pdfMode;

      void setup();
    };
  }
}
#endif