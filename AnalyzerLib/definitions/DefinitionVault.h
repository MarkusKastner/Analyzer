#ifndef DEFINITIONVAULT_H
#define DEFINITIONVAULT_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <memory>
#include <vector>
#include "DefinitionSource.h"

namespace analyzer{
  namespace definition{
    class IMEX DefinitionVault
    {
    public:
      DefinitionVault();
      virtual ~DefinitionVault();

      bool HasDefinitions();
      size_t GetNumSources();
      void AddSource(const std::shared_ptr<DefinitionSource> & source);
      std::shared_ptr<DefinitionSource> GetSourceAt(const size_t index);
      std::shared_ptr<DefinitionSource> GetSource(const std::string & sourceName);
      bool HasSource(const std::string & sourceName);

    private:
      std::vector<std::shared_ptr<DefinitionSource>> * sources;
    };
  }
}

#endif