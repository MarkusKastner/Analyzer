#ifndef TEXTDEFINITION_H
#define TEXTDEFINITION_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <string>

#include "Definition.h"

namespace analyzer{
  namespace definition{
    class IMEX TextDefinition : public Definition
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