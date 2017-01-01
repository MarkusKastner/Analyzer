#ifndef DEFINITIONSOURCE_H
#define DEFINITIONSOURCE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <string>
#include <memory>
#include <vector>

#include "Definition.h"

namespace analyzer{
  namespace definition{
    class IMEX DefinitionSource
    {
    public:
      virtual ~DefinitionSource();

      virtual bool IsInitialized();
     
      const std::string & GetName();

      void AddDefinition(const std::shared_ptr<Definition> & definition);
      size_t GetNumDefinitions();

    protected:
      DefinitionSource();

      void setName(const std::string & name);

    private:
      std::string * name;
      std::vector<std::shared_ptr<Definition>> * definitions;
    };
  }
}
#endif