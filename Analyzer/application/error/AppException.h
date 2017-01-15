/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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