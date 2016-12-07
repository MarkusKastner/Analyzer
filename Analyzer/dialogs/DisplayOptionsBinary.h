#ifndef DISPLAYOPTIONSBINARY_H
#define DISPLAYOPTIONSBINARY_H

#include "DisplayOptions.h"

#include <QRadioButton>

namespace analyzer{
  namespace gui{
    class DisplayOptionsBinary : public DisplayOptions
    {
    public:
      DisplayOptionsBinary(QWidget * parent = 0);
      virtual ~DisplayOptionsBinary();

    private:
      QRadioButton * plainBits;
      QRadioButton * hex;

      void setup();
    };
  }
}
#endif