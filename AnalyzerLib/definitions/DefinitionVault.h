/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DEFINITIONVAULT_H
#define DEFINITIONVAULT_H

#include <memory>
#include <vector>
#include "DefinitionSource.h"

namespace analyzer{
  namespace definition{
    class DefinitionVault
    {
    public:
      DefinitionVault();
      virtual ~DefinitionVault();

      bool HasDefinitions();
      size_t GetNumSources();
      void AddSource(const std::shared_ptr<DefinitionSource> & source);
      std::shared_ptr<DefinitionSource> GetSourceAt(const size_t index);
      std::shared_ptr<DefinitionSource> GetSource(const std::string & sourceName);
      bool HasSource(const std::string & sourceName);

    private:
      std::vector<std::shared_ptr<DefinitionSource>> * sources;
    };
  }
}

#endif