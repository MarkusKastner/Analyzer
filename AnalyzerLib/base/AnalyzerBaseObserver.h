#ifndef ANALYZERBASEOBSERVER_H
#define ANALYZERBASEOBSERVER_H

namespace analyzer{
  namespace base{
    class AnalyzerBaseObserver
    {
    public:
      virtual void NotifyInterprterChange() = 0;
      virtual void NotifyFileChange() = 0;
    };
  }
}
#endif