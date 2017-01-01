#include "TextDefinition.h"

namespace analyzer{
  namespace definition{
    TextDefinition::TextDefinition(const unsigned int & id)
      :Definition(id), expression(new std::string())
    {
    }

    TextDefinition::~TextDefinition()
    {
      delete this->expression;
    }

    void TextDefinition::SetExpression(const std::string & expression)
    {
      *this->expression = expression;
    }

    const std::string & TextDefinition::GetExpression() const
    {
      return *this->expression;
    }
  }
}