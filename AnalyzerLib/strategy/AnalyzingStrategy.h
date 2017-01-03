#ifndef ANALYZINGSTRATEGY_H
#define ANALYZINGSTRATEGY_H

#include "AnalyzerLib\definitions\DefinitionSource.h"
#include "AnalyzerLib\core\ByteCollection.h"

#include <memory>

namespace analyzer{
  namespace strategy{
    class AnalyzingStrategy
    {
    public:
      virtual ~AnalyzingStrategy();

      void SetDefinitions(const std::shared_ptr<definition::DefinitionSource> & definitionSource);
      bool HasDefinitionSource();

      void SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data);
      bool HasData();

    protected:
      AnalyzingStrategy();

    private:
      std::shared_ptr<definition::DefinitionSource> * defSource;
      std::shared_ptr<analyzer::core::ByteCollection> * data;
    };
  }
}


#endif