#ifndef DISPLAYOPTIONSTEXT_H
#define DISPLAYOPTIONSTEXT_H

#include <QWidget>
#include <QRadioButton>

namespace analyzer{
  namespace gui{
    class DisplayOptionsText : public QWidget
    {
      Q_OBJECT
    public:
      DisplayOptionsText(QWidget * parent = 0);
      virtual ~DisplayOptionsText();

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