#ifndef TEXTCHANGEDOBSERVER_H
#define TEXTCHANGEDOBSERVER_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

namespace analyzer{
  namespace interpreter{
    class IMEX TextChangedObserver
    {
    public:
      virtual void NotifyDataChanged() = 0;
    };
  }
}
#endif