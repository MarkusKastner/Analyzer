/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#include "LocalDefinition.h"

namespace analyzer{
  namespace definition{
    LocalDefinition::LocalDefinition()
      :DefinitionSource()
    {

    }

    LocalDefinition::LocalDefinition(const std::string & name)
      :DefinitionSource()
    {
      this->setName(name);
    }

    LocalDefinition::~LocalDefinition()
    {

    }

    bool LocalDefinition::IsInitialized()
    {
      return true;
    }
  }
}