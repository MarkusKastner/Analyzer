#ifndef DISPLAYOPTIONSBINARY_H
#define DISPLAYOPTIONSBINARY_H

#include <QWidget>
#include <QRadioButton>

namespace analyzer{
  namespace gui{
    class DisplayOptionsBinary : public QWidget
    {
    public:
      DisplayOptionsBinary(QWidget * parent = 0);
      virtual ~DisplayOptionsBinary();

    private:
      QRadioButton * binary;
      QRadioButton * hex;

      void setup();
    };
  }
}
#endif