/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DBEXCEPTION_H
#define DBEXCEPTION_H

#include <exception>
#include <string>

namespace analyzer{
  namespace base{
    class DBException : public std::exception
    {
    public:
      DBException()
        : std::exception(), msg(new std::string)
      {
      }

      explicit DBException(const std::string & message)
        : std::exception(), msg(new std::string(message))
      {
      }

      virtual ~DBException()
      {
        delete this->msg;
      }

      const std::string & GetMessage(){
        return *this->msg;
      }

    private:
      std::string * msg;
    };
  }
}
#endif