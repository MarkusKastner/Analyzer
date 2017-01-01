#include "DefinitionSource.h"

#include <algorithm>

#include "AnalyzerLib\base\error\AnalyzerBaseException.h"

namespace analyzer{
  namespace definition{
    DefinitionSource::~DefinitionSource()
    {
      delete this->name;
      delete this->definitions;
    }

    DefinitionSource::DefinitionSource()
      :name(new std::string()), definitions(new std::vector<std::shared_ptr<Definition>>())
    {

    }
  
    bool DefinitionSource::IsInitialized()
    {
      return false;
    }

    const std::string & DefinitionSource::GetName()
    {
      return *this->name;
    }

    void DefinitionSource::setName(const std::string & name)
    {
      *this->name = name;
    }

    void DefinitionSource::AddDefinition(const std::shared_ptr<Definition> & definition)
    {
      if (this->hasID(definition->GetID())){
        throw base::AnalyzerBaseException("ID already in use");
      }
      this->definitions->push_back(definition);
    }

    size_t DefinitionSource::GetNumDefinitions()
    {
      return this->definitions->size();
    }

    size_t DefinitionSource::GetNextFreeID()
    {
      if (this->definitions->empty()){
        return 0;
      }
      std::vector<unsigned int> ids(this->getExisitingIDs());

      unsigned int last = 0;
      for (auto& id : ids){
        if (id - last > 1){
          return last + 1;
        }
        last = id;
      }
      return ids.back() + 1;
    }

    bool DefinitionSource::hasID(const unsigned int & id)
    {
      for (auto& definition : *this->definitions){
        if (definition->GetID() == id){
          return true;
        }
      }
      return false;
    }

    std::vector<unsigned int> DefinitionSource::getExisitingIDs()
    {
      std::vector<unsigned int> ids;
      for (auto& definition : *this->definitions){
        ids.push_back(definition->GetID());
      }
      std::sort(ids.begin(), ids.end());
      return ids;
    }
  }
}