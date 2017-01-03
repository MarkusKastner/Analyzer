#include "AnalyzingStrategy.h"

namespace analyzer{
  namespace strategy{
    AnalyzingStrategy::AnalyzingStrategy()
      : defSource(new std::shared_ptr<definition::DefinitionSource>()),
      data(new std::shared_ptr<analyzer::core::ByteCollection>()),
      analyzingThread(nullptr), sourceLock(new std::recursive_mutex()), dataLock(new std::recursive_mutex()), isAnalyzing(new std::atomic<bool>(false))
    {

    }

    AnalyzingStrategy::~AnalyzingStrategy()
    {
      delete this->defSource;
      delete this->data;

      if (this->analyzingThread != nullptr){
        if (this->analyzingThread->joinable()){
          this->analyzingThread->join();
        }
        delete this->analyzingThread;
      }

      delete this->sourceLock;
      delete this->dataLock;
      delete this->isAnalyzing;
    }

    void AnalyzingStrategy::SetDefinitions(const std::shared_ptr<definition::DefinitionSource> & definitionSource)
    {
      std::lock_guard<std::recursive_mutex> lockDef(*this->sourceLock);
      *this->defSource = definitionSource;
    }

    bool AnalyzingStrategy::HasDefinitionSource()
    {
      std::lock_guard<std::recursive_mutex> lockDef(*this->sourceLock);
      if (*this->defSource){
        return true;
      }
      return false;
    }

    void AnalyzingStrategy::SetData(const std::shared_ptr<analyzer::core::ByteCollection> & data)
    {
      std::lock_guard<std::recursive_mutex> lockData(*this->dataLock);
      *this->data = data;
    }
    
    bool AnalyzingStrategy::HasData()
    {
      std::lock_guard<std::recursive_mutex> lockData(*this->dataLock);
      if (*this->data){
        return true;
      }
      return false;
    }

    void AnalyzingStrategy::StartAnalyzing()
    {
      *this->isAnalyzing = true;
      this->analyzingThread = new std::thread(&AnalyzingStrategy::analyzingRoutine, this);
    }

    bool AnalyzingStrategy::IsAnalyzing()
    {
      return *this->isAnalyzing;
    }

    void AnalyzingStrategy::analyzingRoutine()
    {
      std::lock_guard<std::recursive_mutex> lockDef(*this->sourceLock);
      std::lock_guard<std::recursive_mutex> lockData(*this->dataLock);
      this->analyze(*this->defSource, *this->data);

      *this->isAnalyzing = false;
    }
  }
}