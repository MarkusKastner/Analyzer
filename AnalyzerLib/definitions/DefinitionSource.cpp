#include "DefinitionSource.h"

namespace analyzer{
  namespace definition{
    DefinitionSource::~DefinitionSource()
    {
      delete this->name;
    }

    DefinitionSource::DefinitionSource()
      :name(new std::string())
    {

    }
  
    bool DefinitionSource::IsInitialized()
    {
      return false;
    }

    const std::string & DefinitionSource::GetName()
    {
      return *this->name;
    }

    void DefinitionSource::setName(const std::string & name)
    {
      *this->name = name;
    }
  }
}