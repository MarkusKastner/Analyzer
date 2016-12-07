#ifndef DISPLAYOPTIONS_H
#define DISPLAYOPTIONS_H

#include <QWidget>

namespace analyzer{
  namespace gui{
    class DisplayOptions : public QWidget
    {
    public: 
      virtual ~DisplayOptions();

    protected:
      DisplayOptions(QWidget * parent = 0);
    };
  }
}
#endif