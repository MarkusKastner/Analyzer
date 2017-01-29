/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef DEFINITIONSOURCE_H
#define DEFINITIONSOURCE_H

#include <string>
#include <memory>
#include <vector>

#include "Definition.h"

namespace analyzer{
  namespace definition{
    class DefinitionSource
    {
    public:
      virtual ~DefinitionSource();

      virtual bool IsInitialized();
     
      const std::string & GetName();

      void AddDefinition(const std::shared_ptr<Definition> & definition);
      size_t GetNumDefinitions();
      size_t GetNextFreeID();

      std::vector<std::shared_ptr<Definition>>::iterator begin();
      std::vector<std::shared_ptr<Definition>>::iterator end();

    protected:
      DefinitionSource();

      void setName(const std::string & name);

    private:
      std::string * name;
      std::vector<std::shared_ptr<Definition>> * definitions;

      bool hasID(const unsigned int & id);
      std::vector<unsigned int> getExisitingIDs();
    };
  }
}
#endif