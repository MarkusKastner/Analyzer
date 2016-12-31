#ifndef DEFINITIONSOURCE_H
#define DEFINITIONSOURCE_H

#if _USRDLL
#define IMEX __declspec(dllexport)
#else
#define IMEX __declspec(dllimport)
#endif

namespace analyzer{
  namespace base{
    class IMEX DefinitionSource
    {
    public:
      virtual ~DefinitionSource();

      virtual bool IsInitialized();

    protected:
      DefinitionSource();
    };
  }
}
#endif