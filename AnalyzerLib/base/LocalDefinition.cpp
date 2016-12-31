#include "LocalDefinition.h"

namespace analyzer{
  namespace base{

    LocalDefinition::LocalDefinition()
      :DefinitionSource()
    {

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