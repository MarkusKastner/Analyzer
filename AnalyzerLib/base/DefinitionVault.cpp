#include "DefinitionVault.h"

#include "LocalDefinition.h"

namespace analyzer{
  namespace base{
    DefinitionVault::DefinitionVault()
      :sources(new std::vector<std::shared_ptr<DefinitionSource>>())
    {
      this->sources->push_back(std::shared_ptr<DefinitionSource>(new LocalDefinition("default_ascii")));
    }
    
    DefinitionVault::~DefinitionVault()
    {
      delete this->sources;
    }

    bool DefinitionVault::HasDefinitions()
    {
      return !this->sources->empty();
    }

    size_t DefinitionVault::GetNumSources()
    {
      return this->sources->size();
    }

    std::shared_ptr<DefinitionSource> DefinitionVault::GetSourceAt(const size_t index)
    {
      return this->sources->at(0);
    }
  }
}