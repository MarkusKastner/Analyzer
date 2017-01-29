/* Copyright (C) 2016-2017 - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Markus Kastner <markus.kastner@marscode.at>
*/

#ifndef TEXTDEFINITION_H
#define TEXTDEFINITION_H

#include <string>

#include "Definition.h"

namespace analyzer{
  namespace definition{
    class TextDefinition : public Definition
    {
    public:
      explicit TextDefinition(const unsigned int & id);
      virtual ~TextDefinition();

      void SetExpression(const std::string & expression);
      const std::string & GetExpression() const;

    private:
      std::string *expression;
    };
  }
}
#endif