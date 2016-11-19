#include "CoreException.h"

namespace analyzer{
  namespace core{

    CoreException::CoreException(const std::string & what)
      : std::exception(what.c_str())
    {

    }

    CoreException::~CoreException()
    {

    }

  }
}
