#ifndef IOACTIONOBSERVER_H
#define IOACTIONOBSERVER_H

namespace analyzer{
  namespace app{
    class IOActionObserver
    {
    public:
      virtual void NotifyDataLoad() = 0;
    };
  }
}

#endif