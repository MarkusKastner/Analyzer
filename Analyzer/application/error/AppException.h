#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include <exception>
#include <string>

namespace analyzer{
  namespace app{
    class AppException : public std::exception
    {
    public:
      explicit AppException(const std::string & what);
      virtual ~AppException();
    };
  }
}
#endif