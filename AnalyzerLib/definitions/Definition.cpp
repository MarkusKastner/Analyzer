#include "Definition.h"

namespace analyzer{
  namespace definition{
    Definition::Definition(const unsigned int & id)
      :id(id), description(new std::string())
    {
    }

    Definition::~Definition()
    {
      delete this->description;
    }

    const unsigned int & Definition::GetID()
    {
      return this->id;
    }

    void Definition::SetDescription(const std::string & description)
    {
      *this->description = description;
    }

    const std::string & Definition::GetDescription()
    {
      return *this->description;
    }
  }
}