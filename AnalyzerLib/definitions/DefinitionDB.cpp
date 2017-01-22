/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "DefinitionDB.h"

#include "AnalyzerLib\base\error\DBException.h"

namespace analyzer{
  namespace definition{
    DefinitionDB::DefinitionDB()
      :DefinitionSource()
    {
    }

    DefinitionDB::~DefinitionDB()
    {
    }

    void DefinitionDB::Connect(const std::string & address, const int & port, const std::string & user, const std::string & password)
    {

    }

    bool DefinitionDB::IsInitialized()
    {
      return false;
    }
  }
}