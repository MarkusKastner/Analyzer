#ifndef LOCALDEFINITION_H
#define LOCALDEFINITION_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include "DefinitionSource.h"

#include <string>

namespace analyzer{
  namespace base{
    class IMEX LocalDefinition : public DefinitionSource
    {
    public:
      LocalDefinition();
      LocalDefinition(const std::string & name);
      virtual ~LocalDefinition();
      virtual bool IsInitialized();
    };
  }
}
#endif