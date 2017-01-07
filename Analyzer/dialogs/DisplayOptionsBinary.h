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