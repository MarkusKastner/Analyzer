/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef ANALYZERBASEEXCEPTION_H
#define ANALYZERBASEEXCEPTION_H

#include <exception>
#include <string>

namespace analyzer{
  namespace base{
    class AnalyzerBaseException : public std::exception
    {
    public:
      AnalyzerBaseException()
        : std::exception()
      {
      }

      explicit AnalyzerBaseException(const std::string & message)
        : std::exception(message.c_str())
      {
      }

      virtual ~AnalyzerBaseException()
      {
      }
    };
  }
}
#endif