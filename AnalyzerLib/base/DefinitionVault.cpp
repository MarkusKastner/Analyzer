#include "DefinitionVault.h"

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
  }
}