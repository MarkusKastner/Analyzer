#ifndef INTERPRETEREXCEPTION_H
#define INTERPRETEREXCEPTION_H

#include <exception>

namespace analyzer{
  namespace interpreter{
    class InterpreterException : public std::exception
    {
    public:
      InterpreterException()
        : std::exception()
      {
      }

      explicit InterpreterException(const std::string & message)
        : std::exception(message.c_str())
      {
      }

      virtual ~InterpreterException()
      {
      }
    };
  }
}
#endif