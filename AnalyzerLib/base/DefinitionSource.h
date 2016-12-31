#ifndef DEFINITIONSOURCE_H
#define DEFINITIONSOURCE_H

namespace analyzer{
  namespace base{
    class DefinitionSource
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