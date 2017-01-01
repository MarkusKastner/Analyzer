#include "Definition.h"

namespace analyzer{
  namespace definition{
    Definition::Definition(const unsigned int & id)
      :id(id)
    {
    }

    Definition::~Definition()
    {
    }

    const unsigned int & Definition::GetID()
    {
      return this->id;
    }
  }
}