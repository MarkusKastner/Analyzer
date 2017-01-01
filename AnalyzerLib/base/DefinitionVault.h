#ifndef DEFINITIONVAULT_H
#define DEFINITIONVAULT_H

#include <memory>
#include <vector>
#include "DefinitionSource.h"

namespace analyzer{
  namespace base{
    class DefinitionVault
    {
    public:
      DefinitionVault();
      virtual ~DefinitionVault();

      bool HasDefinitions();
      size_t GetNumSources();
      void AddSource(const std::shared_ptr<DefinitionSource> & source);
      std::shared_ptr<DefinitionSource> GetSourceAt(const size_t index);

    private:
      std::vector<std::shared_ptr<DefinitionSource>> * sources;
    };
  }
}

#endif