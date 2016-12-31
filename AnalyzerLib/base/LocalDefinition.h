#ifndef LOCALDEFINITION_H
#define LOCALDEFINITION_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include "DefinitionSource.h"

namespace analyzer{
  namespace base{
    class IMEX LocalDefinition : public DefinitionSource
    {
    public:
      LocalDefinition();
      virtual ~LocalDefinition();
      virtual bool IsInitialized();
    };
  }
}
#endif