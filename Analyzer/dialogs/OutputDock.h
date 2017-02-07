#ifndef OUTPUTDOCK_H
#define OUTPUTDOCK_H

#include <QDockWidget>

namespace analyzer {
  namespace gui {
    class OutputDock : public QDockWidget
    {
    public:
      OutputDock(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
      virtual ~OutputDock();

    private:
      void setup();
    };
  }
}

#endif