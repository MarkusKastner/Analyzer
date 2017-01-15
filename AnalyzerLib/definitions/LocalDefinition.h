/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef LOCALDEFINITION_H
#define LOCALDEFINITION_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include "DefinitionSource.h"

#include <string>

namespace analyzer{
  namespace definition{
    class IMEX LocalDefinition : public DefinitionSource
    {
    public:
      LocalDefinition();
      LocalDefinition(const std::string & name);
      virtual ~LocalDefinition();
      virtual bool IsInitialized();
    };
  }
}
#endif