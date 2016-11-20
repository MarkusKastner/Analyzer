#include "AppException.h"

namespace analyzer{
  namespace app{

    AppException::AppException(const std::string & what)
      : std::exception(what.c_str())
    {

    }

    AppException::~AppException()
    {

    }

  }
}
