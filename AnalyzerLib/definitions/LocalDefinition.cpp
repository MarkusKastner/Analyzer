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