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

namespace analyzer{
  namespace base{
    class IMEX DefinitionDB
    {
    public:
      DefinitionDB();
      virtual ~DefinitionDB();

      void Connect(const std::string & address, const int & port, const std::string & user, const std::string & password);
      bool IsConnected();

    private:
      MYSQL * connection;
    };
  }
}

#endif