/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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
