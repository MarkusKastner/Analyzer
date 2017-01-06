#ifndef DISPLAYOPTIONSBINARY_H
#define DISPLAYOPTIONSBINARY_H

#include <QWidget>
#include <QRadioButton>

namespace analyzer{
  namespace gui{
    class DisplayOptionsBinary : public QWidget
    {
      Q_OBJECT
    public:
      DisplayOptionsBinary(QWidget * parent = 0);
      virtual ~DisplayOptionsBinary();

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