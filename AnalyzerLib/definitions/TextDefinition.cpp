/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

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