#ifndef BINARYDOCK_H
#define BINARYDOCK_H

#include <QDockWidget>

namespace analyzer {
  namespace gui {
    class BinaryDock : public QDockWidget
    {
    public:
      BinaryDock(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
      virtual ~BinaryDock();

    private:
      void setup();
    };
  }
}

#endif