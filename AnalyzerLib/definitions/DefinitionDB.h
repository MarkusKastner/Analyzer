/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DEFINITIONDB_H
#define DEFINITIONDB_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#ifdef _WIN32
#include <WinSock2.h>
#endif

#include <string>

#include "mysql.h"

#include "DefinitionSource.h"

namespace analyzer{
  namespace definition{
    class IMEX DefinitionDB : public DefinitionSource
    {
    public:
      DefinitionDB();
      virtual ~DefinitionDB();

      void Connect(const std::string & address, const int & port, const std::string & user, const std::string & password);
      virtual bool IsInitialized();

    private:
      MYSQL * connection;
    };
  }
}

#endif