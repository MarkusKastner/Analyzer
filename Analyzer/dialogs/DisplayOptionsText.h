#ifndef DISPLAYOPTIONSTEXT_H
#define DISPLAYOPTIONSTEXT_H

#include <QWidget>
#include <QRadioButton>

namespace analyzer{
  namespace gui{
    class DisplayOptionsText : public QWidget
    {
    public:
      DisplayOptionsText(QWidget * parent = 0);
      virtual ~DisplayOptionsText();

    private:
      QRadioButton * plainText;
      QRadioButton * xmlMode;
      QRadioButton * pdfMode;

      void setup();
    };
  }
}
#endif