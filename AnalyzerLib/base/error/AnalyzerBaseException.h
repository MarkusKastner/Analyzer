#ifndef ANALYZERBASEEXCEPTION_H
#define ANALYZERBASEEXCEPTION_H

#include <exception>
#include <string>

namespace analyzer{
  namespace base{
    class AnalyzerBaseException : public std::exception
    {
    public:
      AnalyzerBaseException()
        : std::exception()
      {
      }

      explicit AnalyzerBaseException(const std::string & message)
        : std::exception(message.c_str())
      {
      }

      virtual ~AnalyzerBaseException()
      {
      }
    };
  }
}
#endif