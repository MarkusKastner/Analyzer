#include "DefinitionVault.h"

#include "LocalDefinition.h"

namespace analyzer{
  namespace base{
    DefinitionVault::DefinitionVault()
    {
    }
    
    DefinitionVault::~DefinitionVault()
    {

    }

    bool DefinitionVault::HasDefinitions()
    {
      return true;
    }

    size_t DefinitionVault::GetNumSources()
    {
      return 1;
    }

    std::shared_ptr<DefinitionSource> DefinitionVault::GetSourceAt(const size_t index)
    {
      return std::shared_ptr<DefinitionSource>(new LocalDefinition("default_ascii"));
    }
  }
}