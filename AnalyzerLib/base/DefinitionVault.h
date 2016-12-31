#ifndef DEFINITIONVAULT_H
#define DEFINITIONVAULT_H

namespace analyzer{
  namespace base{
    class DefinitionVault
    {
    public:
      DefinitionVault();
      virtual ~DefinitionVault();

      bool HasDefinitions();

    };
  }
}

#endif