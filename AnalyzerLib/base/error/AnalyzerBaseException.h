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

      enum ErrorCode
      {
        Empty = 0,
        Unknown,
        ApplicationPathNotSet
      };

      AnalyzerBaseException()
        : std::exception(), errorCode(ErrorCode::Empty)
      {
      }

      explicit AnalyzerBaseException(const std::string & message)
        : std::exception(message.c_str()), errorCode(ErrorCode::Empty)
      {
      }

      explicit AnalyzerBaseException(const ErrorCode & errorCode)
        : std::exception(), errorCode(errorCode)
      {
      }

      virtual ~AnalyzerBaseException()
      {
      }

      virtual char const* what() const
      {
        return std::exception::what();
      }

      const ErrorCode & GetErrorCode() const 
      {
        return this->errorCode;
      }

    private:
      ErrorCode errorCode;
    };
  }
}
#endif