#include "AnalyzingStrategy.h"

namespace analyzer{
  namespace strategy{
    AnalyzingStrategy::AnalyzingStrategy()
      : defSource(new std::shared_ptr<definition::DefinitionSource>()),
      data(new std::shared_ptr<analyzer::core::ByteCollection>())
    {

    }

    AnalyzingStrategy::~AnalyzingStrategy()
    {
      delete this->defSource;
      delete this->data;
    }

    void AnalyzingStrategy::SetDefinitions(const std::shared_ptr<definition::DefinitionSource> & definitionSource)
    {
      *this->defSource = definitionSource;
    }

    bool AnalyzingStrategy::HasDefinitionSource()
    {
      if (*this->defSource){
        return true;
      }
      return false;
    }

    void AnalyzingStrategy::SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      *this->data = data;
    }
    
    bool AnalyzingStrategy::HasData()
    {
      if (*this->data){
        return true;
      }
      return false;
    }
  }
}