#ifndef ANALYZEDOCK_H
#define ANALYZEDOCK_H

#include <QDockWidget>

namespace analyzer {
  namespace gui {
    class AnalyzeDock : public QDockWidget
    {
    public:
      AnalyzeDock(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
      virtual ~AnalyzeDock();

    private:
      void setup();
    };
  }
}
#endif