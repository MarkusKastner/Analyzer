#ifndef TEXTCHANGEDOBSERVER_H
#define TEXTCHANGEDOBSERVER_H

namespace analyzer{
  namespace interpreter{
    class TextChangedObserver
    {
    public:
      virtual void NotifyDataChanged() = 0;
    };
  }
}
#endif