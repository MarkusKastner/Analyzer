/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef CONTENTCHECKEXCEPTION_H
#define CONTENTCHECKEXCEPTION_H

#include <exception>
#include <string>

namespace analyzer {
  namespace checker {
    class ContentCheckException : public std::exception
    {
    public:
      ContentCheckException()
        : std::exception()
      {
      }

      explicit ContentCheckException(const std::string & message)
        : std::exception(message.c_str())
      {
      }

      virtual ~ContentCheckException()
      {
      }

    };
  }
}
#endif