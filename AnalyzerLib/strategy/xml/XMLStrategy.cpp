#include "XMLStrategy.h"

namespace analyzer{
  namespace strategy{
    XMLStrategy::XMLStrategy()
      :AnalyzingStrategy()
    {

    }

    XMLStrategy::~XMLStrategy()
    {

    }


    void XMLStrategy::analyze(const std::shared_ptr<definition::DefinitionSource> & definitions, const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {

    }

    bool XMLStrategy::compareResult(const std::shared_ptr<Result> & result1, const std::shared_ptr<Result> & result2)
    {
      return false;
    }

  }
}