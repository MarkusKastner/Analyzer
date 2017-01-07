#ifndef DISPLAYOPTIONSTEXT_H
#define DISPLAYOPTIONSTEXT_H

#include <QWidget>
#include <QRadioButton>

#include "AnalyzerLib\base\BaseData.h"

namespace analyzer{
  namespace gui{
    class DisplayOptionsText : public QWidget
    {
      Q_OBJECT
    public:
      DisplayOptionsText(QWidget * parent = 0);
      virtual ~DisplayOptionsText();

      base::DetailFormat GetFormat();

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