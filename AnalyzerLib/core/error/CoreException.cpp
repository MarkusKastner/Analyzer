/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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
