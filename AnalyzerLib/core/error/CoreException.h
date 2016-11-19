#ifndef COREEXCEPTION_H
#define COREEXCEPTION_H

#include <exception>
#include <string>

namespace analyzer{
  namespace core{
    class CoreException : public std::exception
    {
    public:
      explicit CoreException(const std::string & what);
      virtual ~CoreException();
    };
  }
}
#endif