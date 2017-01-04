#ifndef XMLSTRATEGY_H
#define XMLSTRATEGY_H

#include "AnalyzerLib\strategy\AnalyzingStrategy.h"

namespace analyzer{
  namespace strategy{
    class XMLStrategy : public AnalyzingStrategy
    {
    public:
      XMLStrategy();
      virtual ~XMLStrategy();

    protected:
      virtual void analyze(const std::shared_ptr<definition::DefinitionSource> & definitions, const std::shared_ptr<analyzer::core::ByteCollection> & data);
      virtual bool compareResult(const std::shared_ptr<Result> & result1, const std::shared_ptr<Result> & result2);
    };
  }
}
#endif