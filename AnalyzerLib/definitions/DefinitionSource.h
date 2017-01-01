#ifndef DEFINITIONSOURCE_H
#define DEFINITIONSOURCE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

#include <string>

namespace analyzer{
  namespace base{
    class IMEX DefinitionSource
    {
    public:
      virtual ~DefinitionSource();

      virtual bool IsInitialized();
      
      const std::string & GetName();

    protected:
      DefinitionSource();

      void setName(const std::string & name);

    private:
      std::string * name;
    };
  }
}
#endif