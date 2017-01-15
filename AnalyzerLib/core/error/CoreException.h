/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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