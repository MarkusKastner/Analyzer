#ifndef LOCALDEFINITION_H
#define LOCALDEFINITION_H

#include "DefinitionSource.h"

namespace analyzer{
  namespace base{
    class LocalDefinition : public DefinitionSource
    {
    public:
      LocalDefinition();
      virtual ~LocalDefinition();
      virtual bool IsInitialized();
    };
  }
}
#endif