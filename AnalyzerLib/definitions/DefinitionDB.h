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