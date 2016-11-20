#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>

namespace analyzer{
  namespace app{
    class IOActions;
  }
  namespace gui{
    class MainWindow;
    class Actions : public QObject
    {
      Q_OBJECT
    public:
      Actions(MainWindow * mainWindow, app::IOActions * ioActions);
      virtual ~Actions();

      void OnOpen();

    private:
      MainWindow * mainWindow;
      app::IOActions * ioActions;

      void throwIOActions();
      void throwMainWindow();
    };
  }
}
#endif